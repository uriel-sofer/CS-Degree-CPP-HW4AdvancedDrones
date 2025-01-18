#ifndef DRONE_H
#define DRONE_H

#include "DirectionalVector.h"

class Drone {
protected:
    static DirectionalVector TARGET;

    unsigned int instanceID; // Unique ID
    DirectionalVector location;
    DirectionalVector velocity;
    DirectionalVector PB; // Personal Best
    static unsigned int counter; // Counts instances for ID-ing
    const char droneType;

public:
    Drone();
    Drone(DirectionalVector loc, DirectionalVector vel, const DirectionalVector& target, char droneType);
    Drone(const Drone& other);
    Drone(Drone&& other);
    Drone& operator=(const Drone& other);
    Drone& operator=(Drone&& other);
    virtual ~Drone();

    unsigned int getID() const;
    DirectionalVector getLocation() const;
    DirectionalVector getVelocity() const;
    char getDroneType() const;
    void setPB(const DirectionalVector& directional_vector);
    DirectionalVector getPB() const;

    bool isOnTarget(const DirectionalVector& target) const;

    virtual void updateVelocity(const Drone& currentGB) = 0;

    virtual void updateVelocity(const Drone &currentGB, double alpha, double beta, double gamma) = 0;

    virtual void move(const Drone& currentGB);


    /**
 * @brief Equality operator for Drone.
 * @param lhs The left-hand side Drone.
 * @param rhs The right-hand side Drone.
 * @return True if both Drones have the same `instanceID`, false otherwise.
 */
    friend bool operator==(const Drone &lhs, const Drone &rhs)
    {
        return lhs.instanceID == rhs.instanceID;
    }

    /**
     * @brief Inequality operator for Drone.
     * @param lhs The left-hand side Drone.
     * @param rhs The right-hand side Drone.
     * @return True if the `instanceID` values differ, false otherwise.
     */
    friend bool operator!=(const Drone &lhs, const Drone &rhs)
    {
        return !(lhs == rhs);
    }

    /**
     * @brief Less-than operator for Drone.
     * @param lhs The left-hand side Drone.
     * @param rhs The right-hand side Drone.
     * @return True if the `instanceID` of `lhs` is less than that of `rhs`, false otherwise.
     */
    friend bool operator<(const Drone &lhs, const Drone &rhs)
    {
        return lhs.instanceID < rhs.instanceID;
    }

    /**
     * @brief Less-than-or-equal-to operator for Drone.
     * @param lhs The left-hand side Drone.
     * @param rhs The right-hand side Drone.
     * @return True if the `instanceID` of `lhs` is less than or equal to that of `rhs`.
     */
    friend bool operator<=(const Drone &lhs, const Drone &rhs)
    {
        return !(rhs < lhs);
    }

    /**
     * @brief Greater-than operator for Drone.
     * @param lhs The left-hand side Drone.
     * @param rhs The right-hand side Drone.
     * @return True if the `instanceID` of `lhs` is greater than that of `rhs`.
     */
    friend bool operator>(const Drone &lhs, const Drone &rhs)
    {
        return rhs < lhs;
    }

    /**
     * @brief Greater-than-or-equal-to operator for Drone.
     * @param lhs The left-hand side Drone.
     * @param rhs The right-hand side Drone.
     * @return True if the `instanceID` of `lhs` is greater than or equal to that of `rhs`.
     */
    friend bool operator>=(const Drone &lhs, const Drone &rhs)
    {
        return !(lhs < rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const Drone& d);

};

#endif
