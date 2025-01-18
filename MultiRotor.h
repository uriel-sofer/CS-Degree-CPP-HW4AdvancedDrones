#ifndef MULTOROTOR_H
#define MULTOROTOR_H

#include "Drone.h"

class MultiRotor : public Drone {
private:
    static const double ALPHA;
    static const double BETA;
    static const double GAMMA;

public:
    MultiRotor() = default;

    MultiRotor(const DirectionalVector &loc, const DirectionalVector &vel, const DirectionalVector &target,
    char droneType);

    MultiRotor(const MultiRotor &other) = default;

    MultiRotor(MultiRotor &&other) = default;

    MultiRotor& operator=(const MultiRotor &other) = default;

    MultiRotor& operator=(MultiRotor &&other) = default;

    void updateVelocity(const Drone &currentGB, double alpha, double beta, double gamma) override;

    void updateVelocity(const Drone &currentGB) override;
};



#endif //MULTOROTOR_H
