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
     // Can they be const? I really want them to be const
     static int MAX_WIDTH_X;
     static int MAX_HEIGHT_Y;
     static int MIN_HEIGHT_Y;
     static int MIN_WIDTH_X;

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

     /**
      * Initiates the MIN and MAX x and y, using the data from the file. The function is called when Initiating the simulation, after parsing the files
      * @param limits array of limits:
      * - [0] is x_min
      * - [1] is y_min
      * - [2] is x_max
      * - [3] is y_max
      */
     static void setLimits(const int *limits);

     /**
      * Checks if the coordinates are in the limits, used when initiating the target
      * @param x x coordinate
      * @param y y coordinate
      * @return true if valid, false if not
      */
     static bool validateCoordinates(double x, double y);
};

#endif
