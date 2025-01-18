#include "HybridDrone.h"

void HybridDrone::updateVelocity(const Drone &currentGB, const double alpha, const double beta, const double gamma)
{
    SingleRotor::updateVelocity(currentGB, SingleRotor::ALPHA, SingleRotor::BETA, SingleRotor::GAMMA);
}

void HybridDrone::updateVelocity(const Drone &currentGB)
{
    updateVelocity(currentGB, SingleRotor::ALPHA, SingleRotor::BETA, SingleRotor::GAMMA);
}
