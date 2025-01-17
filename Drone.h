#ifndef DRONE_H
#define DRONE_H

#include "DirectionalVector.h"

class Drone {
private:
    static DirectionalVector TARGET;

    unsigned int instanceID; // Unique ID
    DirectionalVector location;
    DirectionalVector velocity;
    DirectionalVector PB; // Personal Best
    static unsigned int counter; // Counts instances for ID-ing

public:
    Drone();
    Drone(DirectionalVector loc, DirectionalVector vel, const DirectionalVector& target);
    Drone(const Drone& other);
    Drone(Drone&& other);
    Drone& operator=(const Drone& other);
    Drone& operator=(Drone&& other);
    ~Drone();

    unsigned int getID() const;
    DirectionalVector getLocation() const;
    DirectionalVector getVelocity() const;
    void setPB(const DirectionalVector& directional_vector);
    DirectionalVector getPB() const;

    bool isOnTarget(const DirectionalVector& target) const;

    void updateVelocity(const Drone& currentGB);

    void move(const Drone& currentGB);

    friend std::ostream& operator<<(std::ostream& os, const Drone& d);

};

#endif
