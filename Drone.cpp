#include "Drone.h"
#include <cstdlib>
#include <iomanip>

unsigned int Drone::counter = 1;
DirectionalVector Drone::TARGET = DirectionalVector();

Drone::Drone() : instanceID(0), location(DirectionalVector()), velocity(DirectionalVector()),
PB(DirectionalVector()), droneType()
{}

Drone::Drone(DirectionalVector loc, DirectionalVector vel, const DirectionalVector& target, const char droneType)
    : instanceID(counter++), location(std::move(loc)), velocity(std::move(vel)),
    PB(DirectionalVector()), droneType(droneType)
{
    TARGET = target;
}

Drone::Drone(const Drone& other)
    : instanceID(other.instanceID), location(other.location),
    velocity(other.velocity), PB(other.PB), droneType(other.droneType)
{}

Drone::Drone(Drone&& other)
    : instanceID(other.instanceID), location(std::move(other.location)),
    velocity(std::move(other.velocity)), PB(std::move(other.PB)), droneType(other.droneType)
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

char Drone::getDroneType() const
{
    return droneType;
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

void Drone::updateVelocity(const Drone& currentGB,const double alpha, const double beta, const double gamma)
{
    const double randomNum1 = static_cast<double>(std::rand()) / RAND_MAX;
    const double randomNum2 = static_cast<double>(std::rand()) / RAND_MAX;

    velocity = alpha *  velocity +
            beta * randomNum1 * (PB - location) +
            gamma * randomNum2 * (currentGB.location - location);
}

void Drone::move(const Drone& currentGB)
{
    location = location + velocity;
}

std::ostream& operator<<(std::ostream& os, const Drone& d)
{
    if (d.getID() != 0)
    {
        os << std::fixed <<std::setprecision(2); // Set fixed-point format with 2 decimal places
        os << "Drone " << d.instanceID
                << " type " << d.droneType
                << " at " << d.location
                << " with speed " << d.velocity
                << ". PB: " << d.PB
                << " Distance: " << d.getLocation().euclideanDistance(Drone::TARGET)
        << std::endl;
    }
    return os;
}

