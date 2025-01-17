#ifndef POINT_H
#define POINT_H

#include <iostream>

/**
 * Represents a point, used with DirectionalVector
 */
class Point {
protected:
     double x, y;
     virtual void limitPoint(); // Limits the points to given bounds (below)

public:
     static constexpr int MAX_WIDTH_X = 72;
     static constexpr int MAX_HEIGHT_Y = 42;

     Point();
     Point(double x, double y);
     Point(const Point& other);
     Point(Point&& other);
     Point& operator=(const Point& other);
     Point& operator=(Point&& other);
     virtual ~Point();

     double getX() const;
     void setX(double x);
     double getY() const;
     void setY(double y);

     double distance(const Point& other) const;

     friend std::ostream& operator<<(std::ostream& os, const Point& p);
     bool operator==(const Point& point) const;
};

#endif
