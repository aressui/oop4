#pragma once
#include "point.h"
#include <memory>
#include <vector>

template <Scalar T>
class Figure {
protected:
    std::unique_ptr<Point<T>> center_point;
    
public:
    Figure() : center_point(std::make_unique<Point<T>>()) {}
    Figure(T x, T y) : center_point(std::make_unique<Point<T>>(x, y)) {}
    virtual ~Figure() = default;
    
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual Point<T> getCenter() const = 0;
    virtual std::vector<Point<T>> getVertices() const = 0;
    
    explicit operator double() const {
        return area();
    }
    
    bool operator==(const Figure& other) const {
        return area() == other.area();
    }
    
    bool operator<(const Figure& other) const {
        return area() < other.area();
    }
};