#pragma once
#include <iostream>
#include <concepts>
#include <memory>
#include <vector>
#include <stdexcept>

template <class T>
concept Arrayable = std::is_default_constructible_v<T> && 
                   std::is_copy_constructible_v<T> && 
                   std::is_move_constructible_v<T>;

template <Arrayable T>
class Array {
private:
    size_t count;
    size_t max_capacity;
    std::unique_ptr<T[]> data;
    
    void increase_capacity(size_t new_cap) {
        auto new_data = std::make_unique<T[]>(new_cap);
        
        for (size_t idx = 0; idx < count; ++idx) {
            new_data[idx] = std::move(data[idx]);
        }
        
        data = std::move(new_data);
        max_capacity = new_cap;
    }

public:
    Array() : count(0), max_capacity(10), data(std::make_unique<T[]>(10)) {}

    Array(std::initializer_list<T> items) {
        count = items.size();
        max_capacity = count * 2;
        data = std::make_unique<T[]>(max_capacity);
        
        size_t idx = 0;
        for (auto& elem : items) {
            data[idx++] = elem;
        }
    }

    Array(const Array& other) {
        count = other.count;
        max_capacity = other.max_capacity;
        data = std::make_unique<T[]>(max_capacity);

        for (size_t idx = 0; idx < count; ++idx) {
            data[idx] = other.data[idx];
        }
    }

    Array(Array&& other) noexcept {
        count = other.count;
        max_capacity = other.max_capacity;
        data = std::move(other.data);

        other.count = 0;
        other.max_capacity = 0;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            count = other.count;
            max_capacity = other.max_capacity;
            data = std::make_unique<T[]>(max_capacity);

            for (size_t idx = 0; idx < count; ++idx) {
                data[idx] = other.data[idx];
            }
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            count = other.count;
            max_capacity = other.max_capacity;
            data = std::move(other.data);

            other.count = 0;
            other.max_capacity = 0;
        }
        return *this;
    }

    void add(const T& elem) {
        if (count >= max_capacity) {
            increase_capacity(max_capacity * 2);
        }
        data[count++] = elem;
    }

    void remove(size_t pos) {
        if (pos >= count) {
            throw std::out_of_range("Index out of range");
        }
        
        for (size_t idx = pos; idx < count - 1; ++idx) {
            data[idx] = std::move(data[idx + 1]);
        }
        --count;
    }

    T& operator[](size_t pos) {
        if (pos >= count) {
            throw std::out_of_range("Index out of range");
        }
        return data[pos];
    }

    const T& operator[](size_t pos) const {
        if (pos >= count) {
            throw std::out_of_range("Index out of range");
        }
        return data[pos];
    }

    size_t size() const { return count; }
    size_t capacity() const { return max_capacity; }
};