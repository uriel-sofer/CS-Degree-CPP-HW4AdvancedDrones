#ifndef DIRECTIONALVECTOR_H
#define DIRECTIONALVECTOR_H


#include "Point.h"

class DirectionalVector : public Point {

public:
    DirectionalVector();
    DirectionalVector(double x, double y);
    explicit DirectionalVector(const Point& p);
    DirectionalVector(const DirectionalVector &other);
    DirectionalVector(DirectionalVector &&other);
    DirectionalVector &operator=(const DirectionalVector &other);
    DirectionalVector &operator=(DirectionalVector &&other);
    ~DirectionalVector();

    DirectionalVector operator+(const DirectionalVector& other) const;
    DirectionalVector& operator+=(const DirectionalVector& other);
    DirectionalVector operator-(const DirectionalVector& other) const;

    bool operator==(const DirectionalVector& other) const;

    double euclideanDistance(const Point& point) const;
    double euclideanDistance(const DirectionalVector& direction) const;
    /**
     * Floors the vector's coordinates, to know if we are on target
     * @return DirectionalVector with only the whole parts of x and y
     */
    DirectionalVector floorVector() const;

    friend std::ostream& operator<<(std::ostream& os, const DirectionalVector& vec);
    friend DirectionalVector operator*(double scalar, const DirectionalVector& vector);
};

#endif //DIRECTIONALVECTOR_H
