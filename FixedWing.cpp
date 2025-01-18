#include "FixedWing.h"

const double FixedWing::ALPHA = 0.25;
const double FixedWing::BETA = 1;
const double FixedWing::GAMMA = 1;

FixedWing::FixedWing(const DirectionalVector &loc, const DirectionalVector &vel, const DirectionalVector &target,
    const char droneType) : Drone(loc, vel, target, droneType)
{}

void FixedWing::updateVelocity(const Drone &currentGB, const double alpha, const double beta, const double gamma)
{
    Drone::updateVelocity(currentGB, ALPHA, BETA, GAMMA);
}

void FixedWing::updateVelocity(const Drone &currentGB)
{
    updateVelocity(currentGB, ALPHA, BETA, GAMMA);
}
