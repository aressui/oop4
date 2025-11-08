#pragma once
#include "figure.h"
#include <vector>

template <Scalar T>
class Square : public Figure<T> {
private:
    T side_length;
    
public:
    Square() : side_length(1) {}
    Square(T side) : side_length(side) {}
    Square(T x, T y, T side) : side_length(side) {
        this->center_point = std::make_unique<Point<T>>(x, y);
    }
    
    double area() const override {
        return static_cast<double>(side_length * side_length);
    }
    
    void print(std::ostream& os) const override {
        os << "Square: side=" << side_length << ", area=" << area() 
           << ", center=" << *this->center_point;
    }
    
    Point<T> getCenter() const override {
        return Point<T>(this->center_point->getX(), this->center_point->getY());
    }
    
    std::vector<Point<T>> getVertices() const override {
        T half = side_length / 2;
        T cx = this->center_point->getX();
        T cy = this->center_point->getY();
        
        std::vector<Point<T>> points;
        points.emplace_back(cx - half, cy + half);
        points.emplace_back(cx + half, cy + half);
        points.emplace_back(cx + half, cy - half);
        points.emplace_back(cx - half, cy - half);
        
        return points;
    }
    
    T getSide() const { return side_length; }
    void setSide(T s) { side_length = s; }
    
    friend std::ostream& operator<<(std::ostream& os, const Square& sq) {
        sq.print(os);
        return os;
    }
};