#include "Drone.h"
#include  <ctime>
#include <cmath>
#include <cstdlib>
#include <iomanip>

unsigned int Drone::counter = 0;
DirectionalVector Drone::TARGET = DirectionalVector();

Drone::Drone() : instanceID(0), location(DirectionalVector()), velocity(DirectionalVector()), PB(DirectionalVector())
{}

Drone::Drone(DirectionalVector loc, DirectionalVector vel, const DirectionalVector& target)
    : instanceID(counter++), location(std::move(loc)), velocity(std::move(vel)), PB(DirectionalVector())
{
    TARGET = target;
}

Drone::Drone(const Drone& other)
    : instanceID(other.instanceID), location(other.location), velocity(other.velocity), PB(other.PB)
{}

Drone::Drone(Drone&& other)
    : instanceID(other.instanceID), location(std::move(other.location)), velocity(std::move(other.velocity)), PB(std::move(other.PB))
{}

Drone::~Drone() {}

Drone& Drone::operator=(const Drone& other)
{
    if (this != &other)
    {
        instanceID = other.instanceID;
        location = other.location;
        velocity = other.velocity;
        PB = other.PB;
    }
    return *this;
}

Drone& Drone::operator=(Drone&& other)
{
    if (this != &other)
    {
        instanceID = other.instanceID; // std::move by default
        location = std::move(other.location);
        velocity = std::move(other.velocity);
        PB = std::move(other.PB);
    }
    return *this;
}

unsigned int Drone::getID() const
{
    return instanceID;
}

DirectionalVector Drone::getLocation() const
{
    return location;
}

DirectionalVector Drone::getVelocity() const
{
    return velocity;
}

DirectionalVector Drone::getPB() const
{
    return PB;
}

bool Drone::isOnTarget(const DirectionalVector& target) const
{
    return location.floorVector() == target.floorVector();
}

void Drone::setPB(const DirectionalVector& directional_vector)
{
    PB = directional_vector;
}

void Drone::updateVelocity(const Drone& currentGB)
{
    // Generate two random numbers between 0 and 1
    const double randomNum1 = static_cast<double>(std::rand()) / RAND_MAX;
    const double randomNum2 = static_cast<double>(std::rand()) / RAND_MAX;

    velocity = 0.25 *  velocity +
            randomNum1 * (PB - location) +
            randomNum2 * (currentGB.location - location);
}

void Drone::move(const Drone& currentGB)
{
    /*
     * Not sure what is the correct order of these lines, but it doesn't seem to matter
     */
    location = location + velocity;
}

std::ostream& operator<<(std::ostream& os, const Drone& d)
{
    os << std::fixed <<std::setprecision(5); // Set fixed-point format with 2 decimal places
    os << "Drone " << d.instanceID
       << " at " << d.location
       << " with speed " << d.velocity
       << ". PB: " << d.PB
       << " Distance: " << d.getLocation().euclideanDistance(Drone::TARGET);
    return os;
}

