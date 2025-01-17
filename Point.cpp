#include "Point.h"
#include <cmath>


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

void Point::limitPoint()
{
    if (this->x > MAX_WIDTH_X) this->x = MAX_WIDTH_X;
    if (this->x < 0) this->x = 0;

    if (this->y > MAX_HEIGHT_Y) this->y = MAX_HEIGHT_Y;
    if (this->y < 0) this->y = 0;
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
