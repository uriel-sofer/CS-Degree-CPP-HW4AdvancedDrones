#ifndef FIXEDWING_H
#define FIXEDWING_H

#include "Drone.h"

class FixedWing : public virtual Drone{
private:
    static const double ALPHA;
    static const double BETA;
    static const double GAMMA;

public:
    FixedWing() = default;

    FixedWing(const DirectionalVector &loc, const DirectionalVector &vel, const DirectionalVector &target,
        char droneType);

    FixedWing(const FixedWing &other) = default;

    FixedWing(FixedWing &&other) = default;

    FixedWing & operator=(const FixedWing &other) = default;

    FixedWing & operator=(FixedWing &&other);

    void updateVelocity(const Drone &currentGB, double alpha, double beta, double gamma) override;

    void updateVelocity(const Drone &currentGB) override;
};



#endif //FIXEDWING_H
