#pragma once
#include <concepts>
#include <iostream>
#include <memory>

template <typename T>
concept Scalar = std::is_default_constructible_v<T> && 
                (std::integral<T> || std::is_floating_point_v<T>);

template <Scalar T>
class Point {
private:
    T x, y;
    
public:
    Point() : x(0), y(0) {}
    Point(T x_val, T y_val) : x(x_val), y(y_val) {}
    
    T getX() const { return x; }
    T getY() const { return y; }
    
    void setX(T x_val) { x = x_val; }
    void setY(T y_val) { y = y_val; }
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    Point operator/(T div) const {
        return Point(x / div, y / div);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};