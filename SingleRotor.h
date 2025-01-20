#ifndef SINGLEROTOR_H
#define SINGLEROTOR_H

#include "Drone.h"


class SingleRotor : public virtual Drone {
protected:
    static const double ALPHA;
    static const double BETA;
    static const double GAMMA;

public:
    SingleRotor() = default;

    SingleRotor(const DirectionalVector &loc, const DirectionalVector &vel, const DirectionalVector &target,
        char droneType);

    SingleRotor(const SingleRotor &other) = default;

    SingleRotor(SingleRotor &&other) = default;

    SingleRotor& operator=(const SingleRotor &other) = default;

    SingleRotor& operator=(SingleRotor &&other);

    void updateVelocity(const Drone &currentGB, double alpha, double beta, double gamma) override;

    void updateVelocity(const Drone &currentGB) override;
};



#endif //SINGLEROTOR_H
