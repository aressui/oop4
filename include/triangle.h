#pragma once
#include "figure.h"
#include <cmath>
#include <vector>

template <Scalar T>
class Triangle : public Figure<T> {
private:
    T side_length;
    
public:
    Triangle() : side_length(1) {}
    Triangle(T side) : side_length(side) {}
    Triangle(T x, T y, T side) : side_length(side) {
        this->center_point = std::make_unique<Point<T>>(x, y);
    }
    
    double area() const override {
        return (std::sqrt(3) / 4) * static_cast<double>(side_length * side_length);
    }
    
    void print(std::ostream& os) const override {
        os << "Triangle: side=" << side_length << ", area=" << area() 
           << ", center=" << *this->center_point;
    }
    
    Point<T> getCenter() const override {
        return Point<T>(this->center_point->getX(), this->center_point->getY());
    }
    
    std::vector<Point<T>> getVertices() const override {
        double h = (side_length * std::sqrt(3)) / 2;
        T cx = this->center_point->getX();
        T cy = this->center_point->getY();
        
        std::vector<Point<T>> points;
        points.emplace_back(cx, cy + h / 3);
        points.emplace_back(cx - side_length/2, cy - 2*h/3);
        points.emplace_back(cx + side_length/2, cy - 2*h/3);
        
        return points;
    }
    
    T getSide() const { return side_length; }
    void setSide(T s) { side_length = s; }
    
    friend std::ostream& operator<<(std::ostream& os, const Triangle& tri) {
        tri.print(os);
        return os;
    }
};