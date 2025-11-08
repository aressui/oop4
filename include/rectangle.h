#pragma once
#include "figure.h"
#include <vector>

template <Scalar T>
class Rectangle : public Figure<T> {
private:
    T width, height;
    
public:
    Rectangle() : width(1), height(1) {}
    Rectangle(T w, T h) : width(w), height(h) {}
    Rectangle(T x, T y, T w, T h) : width(w), height(h) {
        this->center_point = std::make_unique<Point<T>>(x, y);
    }
    
    double area() const override {
        return static_cast<double>(width * height);
    }
    
    void print(std::ostream& os) const override {
        os << "Rectangle: width=" << width << ", height=" << height 
           << ", area=" << area() << ", center=" << *this->center_point;
    }
    
    Point<T> getCenter() const override {
        return Point<T>(this->center_point->getX(), this->center_point->getY());
    }
    
    std::vector<Point<T>> getVertices() const override {
        T half_w = width / 2;
        T half_h = height / 2;
        T cx = this->center_point->getX();
        T cy = this->center_point->getY();
        
        std::vector<Point<T>> points;
        points.emplace_back(cx - half_w, cy + half_h);
        points.emplace_back(cx + half_w, cy + half_h);
        points.emplace_back(cx + half_w, cy - half_h);
        points.emplace_back(cx - half_w, cy - half_h);
        
        return points;
    }
    
    T getWidth() const { return width; }
    T getHeight() const { return height; }
    void setWidth(T w) { width = w; }
    void setHeight(T h) { height = h; }
    
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect) {
        rect.print(os);
        return os;
    }
};