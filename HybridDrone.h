#ifndef HYBRIDDRONE_H
#define HYBRIDDRONE_H

#include "FixedWing.h"
#include "SingleRotor.h"


class HybridDrone : virtual public SingleRotor, virtual public FixedWing{
public:
    HybridDrone(const DirectionalVector &loc, const DirectionalVector &vel, const DirectionalVector &target,
        const char droneType)
        : Drone(loc, vel, target, droneType)
    {}

    HybridDrone(const HybridDrone &other)
        : SingleRotor(other),
          FixedWing(other)
    {}

    HybridDrone(HybridDrone &&other) noexcept
        : SingleRotor(std::move(other)),
          FixedWing(std::move(other))
    {}

    HybridDrone & operator=(const HybridDrone &other)
    {
        if (this == &other)
            return *this;
        SingleRotor::operator =(other);
        FixedWing::operator =(other);
        return *this;
    }

    HybridDrone & operator=(HybridDrone &&other) noexcept
    {
        if (this == &other)
            return *this;
        SingleRotor::operator =(std::move(other));
        FixedWing::operator =(std::move(other));
        return *this;
    }

    void updateVelocity(const Drone &currentGB, double alpha, double beta, double gamma) override;

    void updateVelocity(const Drone &currentGB) override;
};



#endif //HYBRIDDRONE_H
