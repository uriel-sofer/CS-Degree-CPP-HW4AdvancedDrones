#include <cmath>
#include <iomanip>
#include "DirectionalVector.h"


DirectionalVector::DirectionalVector() : Point()
{}

DirectionalVector::DirectionalVector(const double x, const double y) : Point(x, y)
{}

DirectionalVector::DirectionalVector(const Point& p) : Point(p)
{}

DirectionalVector::DirectionalVector(const DirectionalVector& other) : Point(other)
{}

DirectionalVector::DirectionalVector(DirectionalVector&& other) : Point(std::move(other))
{}

DirectionalVector& DirectionalVector::operator=(const DirectionalVector& other)
{
    if (this != &other)
    {
        Point::operator=(other);
    }
    return *this;
}

DirectionalVector& DirectionalVector::operator=(DirectionalVector&& other)
{
    if (this != &other)
    {
        Point::operator=(std::move(other));
    }
    return *this;
}

DirectionalVector::~DirectionalVector()
{}

DirectionalVector DirectionalVector::operator+(const DirectionalVector& other) const
{
    return DirectionalVector(getX() + other.getX(), getY() + other.getY());
}

DirectionalVector& DirectionalVector::operator+=(const DirectionalVector& other)
{
    setX(getX() + other.getX());
    setY(getY() + other.getY());
    return *this;
}

DirectionalVector DirectionalVector::operator-(const DirectionalVector& other) const
{
    return DirectionalVector(getX() - other.getX(), getY() - other.getY());
}

bool DirectionalVector::operator==(const DirectionalVector& other) const
{
    return getX() == other.getX() && getY() == other.getY();
}

double DirectionalVector::euclideanDistance(const Point& point) const
{
    return Point::distance(point);
}

double DirectionalVector::euclideanDistance(const DirectionalVector& direction) const
{
    return Point::distance(direction);
}

std::ostream& operator<<(std::ostream& os, const DirectionalVector& vec)
{
    os << vec.getX() << " " << vec.getY();
    return os;
}

DirectionalVector operator*(const double scalar, const DirectionalVector& vector)
{
    return DirectionalVector(scalar * vector.getX(), scalar * vector.getY());
}

DirectionalVector DirectionalVector::floorVector() const
{
    return DirectionalVector(std::floor(this->getX()), std::floor(this->getY()));
}