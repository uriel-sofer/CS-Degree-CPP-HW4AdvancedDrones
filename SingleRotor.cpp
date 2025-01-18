#include "SingleRotor.h"

const double SingleRotor::ALPHA = 0.01;
const double SingleRotor::BETA = -0.1;
const double SingleRotor::GAMMA = -0.25;

SingleRotor::SingleRotor(const DirectionalVector &loc, const DirectionalVector &vel, const DirectionalVector &target,
    const char droneType) : Drone(loc, vel, target, droneType)
{}

void SingleRotor::updateVelocity(const Drone &currentGB, const double alpha, const double beta, const double gamma)
{
    Drone::updateVelocity(currentGB, ALPHA, BETA, GAMMA);
}

void SingleRotor::updateVelocity(const Drone &currentGB)
{
    updateVelocity(currentGB, ALPHA, BETA, GAMMA);
}
