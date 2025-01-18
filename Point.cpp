#include "Point.h"
#include <cmath>

#include "Point.h"

// Define static members
int Point::MAX_WIDTH_X = 72;
int Point::MAX_HEIGHT_Y = 42;
int Point::MIN_WIDTH_X = 0;
int Point::MIN_HEIGHT_Y = 0;

Point::Point() : x(0), y(0) {}

Point::Point(const double x, const double y) : x(x), y(y)
{
    Point::limitPoint();
}

Point::Point(const Point& other) : x(other.x), y(other.y) {}

Point::Point(Point&& other) : x(other.x), y(other.y)
{
    other.x = 0;
    other.y = 0;
}

Point& Point::operator=(const Point& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}

Point& Point::operator=(Point&& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        other.x = 0;
        other.y = 0;
    }
    return *this;
}

Point::~Point() {}

double Point::getX() const
{
    return x;
}

void Point::setX(const double x)
{
    this->x = x;
    limitPoint();
}

double Point::getY() const
{
    return y;
}

void Point::setY(const double y)
{
    this->y = y;
    limitPoint();
}

bool Point::operator==(const Point& point) const
{
    return x == point.x and y == point.y;
}

void Point::setLimits(const int* limits)
{
    MIN_WIDTH_X = limits[0];
    MIN_HEIGHT_Y = limits[1];
    MAX_WIDTH_X = limits[2];
    MAX_HEIGHT_Y = limits[3];
}

bool Point::validateCoordinates(const double x, const double y)
{
    return  not (x < MIN_WIDTH_X or y < MIN_HEIGHT_Y or x > MAX_WIDTH_X or y > MAX_HEIGHT_Y);
}

void Point::limitPoint()
{
    if (this->x > MAX_WIDTH_X) this->x = MAX_WIDTH_X;
    if (this->x < MIN_WIDTH_X) this->x = MIN_WIDTH_X;

    if (this->y > MAX_HEIGHT_Y) this->y = MAX_HEIGHT_Y;
    if (this->y < MIN_HEIGHT_Y) this->y = MIN_HEIGHT_Y;
}

double Point::distance(const Point& other) const
{
    return std::sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
