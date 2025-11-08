#include <iostream>
#include <memory>
#include <iomanip>

#include "include/point.h"
#include "include/figure.h"
#include "include/triangle.h"
#include "include/square.h"
#include "include/rectangle.h"
#include "include/array.h"

int main() {
    auto triangle = std::make_shared<Triangle<int>>(0, 0, 5);
    auto square = std::make_shared<Square<int>>(1, 1, 4);
    auto rectangle = std::make_shared<Rectangle<int>>(2, 2, 6, 3);
    
    std::cout << "Created figures:" << std::endl;
    std::cout << *triangle << std::endl;
    std::cout << *square << std::endl;
    std::cout << *rectangle << std::endl;
    
    std::cout << "\nTriangle vertices:" << std::endl;
    auto tri_vertices = triangle->getVertices();
    for (const auto& vertex : tri_vertices) {
        std::cout << "  " << vertex << std::endl;
    }
    
    Array<std::shared_ptr<Figure<int>>> figures;
    
    figures.add(std::make_shared<Triangle<int>>(0, 0, 3));
    figures.add(std::make_shared<Square<int>>(1, 1, 4));
    figures.add(std::make_shared<Rectangle<int>>(2, 2, 5, 3));
    figures.add(std::make_shared<Triangle<int>>(3, 3, 6));
    
    std::cout << "\nAll figures in array:" << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure " << i << ":" << std::endl;
        std::cout << "  Type: ";
        figures[i]->print(std::cout);
        std::cout << std::endl;
        std::cout << "  Center: " << figures[i]->getCenter() << std::endl;
        std::cout << "  Area: " << figures[i]->area() << std::endl;
        
        auto vertices = figures[i]->getVertices();
        std::cout << "  Vertices: ";
        for (size_t j = 0; j < vertices.size(); ++j) {
            std::cout << vertices[j];
            if (j < vertices.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_area += static_cast<double>(*figures[i]);
    }
    std::cout << "\nTotal area of all figures: " << std::fixed << std::setprecision(2) 
              << total_area << std::endl;
    
    figures.remove(1);
    std::cout << "\nAfter removing figure at index 1, array size: " << figures.size() << std::endl;
    
    Array<std::shared_ptr<Square<double>>> squares;
    squares.add(std::make_shared<Square<double>>(0, 0, 2.5));
    squares.add(std::make_shared<Square<double>>(1, 1, 3.0));
    
    std::cout << "\nSquares array:" << std::endl;
    for (size_t i = 0; i < squares.size(); ++i) {
        std::cout << "[" << i << "] " << *squares[i] << std::endl;
    }
    
    std::cout << "\nDemonstrating move semantics:" << std::endl;
    Array<std::shared_ptr<Figure<int>>> moved_figures = std::move(figures);
    std::cout << "Original array size after move: " << figures.size() << std::endl;
    std::cout << "Moved array size: " << moved_figures.size() << std::endl;
    
    return 0;
}