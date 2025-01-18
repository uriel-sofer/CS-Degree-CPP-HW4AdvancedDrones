#include "MultiRotor.h"

const double MultiRotor::ALPHA = 0.05;
const double MultiRotor::BETA = 0.1;
const double MultiRotor::GAMMA = 0;

MultiRotor::MultiRotor(const DirectionalVector &loc, const DirectionalVector &vel, const DirectionalVector &target,
    const char droneType) : Drone(loc, vel, target, droneType)
{}

void MultiRotor::updateVelocity(const Drone &currentGB, const double alpha, const double beta, const double gamma)
{
    Drone::updateVelocity(currentGB, ALPHA, BETA, GAMMA);
}

void MultiRotor::updateVelocity(const Drone &currentGB)
{
    updateVelocity(currentGB, ALPHA, BETA, GAMMA);
}
