#include <gtest/gtest.h>
#include <memory>
#include <cmath>

#include "../include/point.h"
#include "../include/figure.h"
#include "../include/triangle.h"
#include "../include/square.h"
#include "../include/rectangle.h"
#include "../include/array.h"

TEST(PointTest, ConstructionAndAccess) {
    Point<int> p1(10, 20);
    EXPECT_EQ(p1.getX(), 10);
    EXPECT_EQ(p1.getY(), 20);
}

TEST(FigureTest, TriangleArea) {
    Triangle<int> t(0, 0, 4);
    double expected = (std::sqrt(3) / 4) * 4 * 4;
    EXPECT_NEAR(t.area(), expected, 0.001);
}

TEST(FigureTest, SquareArea) {
    Square<int> s(0, 0, 5);
    EXPECT_DOUBLE_EQ(s.area(), 25.0);
}

TEST(FigureTest, RectangleArea) {
    Rectangle<int> r(0, 0, 4, 6);
    EXPECT_DOUBLE_EQ(r.area(), 24.0);
}

TEST(FigureTest, DoubleConversion) {
    Square<int> s(0, 0, 3);
    double area = static_cast<double>(s);
    EXPECT_DOUBLE_EQ(area, 9.0);
}

TEST(ArrayTest, BasicOperations) {
    Array<std::shared_ptr<Figure<int>>> arr;
    
    arr.add(std::make_shared<Triangle<int>>(0, 0, 3));
    arr.add(std::make_shared<Square<int>>(0, 0, 2));
    
    EXPECT_EQ(arr.size(), 2);
    EXPECT_GT(arr[0]->area(), 0);
}

TEST(ArrayTest, RemoveOperation) {
    Array<int> arr{1, 2, 3, 4, 5};
    
    arr.remove(2);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[2], 4);
}

TEST(ArrayTest, MoveSemantics) {
    Array<int> original{1, 2, 3};
    Array<int> moved = std::move(original);
    
    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(original.size(), 0);
}

TEST(ConceptsTest, ScalarConcept) {
    static_assert(Scalar<int>);
    static_assert(Scalar<double>);
    static_assert(Scalar<float>);
}

TEST(ConceptsTest, ArrayableConcept) {
    static_assert(Arrayable<int>);
    static_assert(Arrayable<std::shared_ptr<Figure<int>>>);
}