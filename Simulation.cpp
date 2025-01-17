#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

Simulation::Simulation(const Config& config, const Init& init) :
target(config.target), AMOUNT(init.dronesAmount), iterations(config.iterations),globalBestIndex(0), forest()
{
    drones = new Drone[AMOUNT];
    for (size_t i = 0; i < AMOUNT; i++)
    {
        new (&drones[i]) Drone(init.initialLocations[i], init.speeds[i], target);
        updatePersonalBest(i);
    }
    updateGlobalBest();
    std::srand(static_cast<unsigned int>(time(nullptr)));
}

Simulation::~Simulation()
{
    delete[] drones;
}

void Simulation::updateGlobalBest()
{
    /* So there can be cases where a drone is on the target, but he isn't the "closest" to the target, such as:
    *Target: (7.00, 7.00)
    Drone 0 at (6.31, 7.00) with speed (1.89, 1.57). PB: (6.31, 7.00) Distance: *0.69*
    Drone 1 at (6.61, 7.50) with speed (1.76, 1.85). PB: (6.61, 7.50) Distance: 0.63
    Drone 2 at (7.01, 8.05) with speed (1.64, 1.98). PB: (7.01, 8.05) Distance: 1.05
    Drone 3 at (7.04, 8.24) with speed (1.67, 1.87). PB: (7.04, 8.24) Distance: 1.25
    Drone 4 at (6.93, 8.03) with speed (1.77, 1.99). PB: (6.93, 8.03) Distance: 1.04
    Drone 5 at (7.11, 7.74) with speed (1.01, 1.28). PB: (7.11, 7.74) Distance: *0.74*
    Global best: Drone 1 at (6.61, 7.50) with speed (1.76, 1.85). PB: (6.61, 7.50) Distance: 0.63
    Drone 5 reached the target!

    Now, it doesn't really matter because the simulation is ending, but I think that while factually another drone is close,
    the drone that is literally on the target should be considered the GB, as he is the "winner".
    */
    for (size_t currentIndex = 0; currentIndex < AMOUNT; currentIndex++)
    {
        if (drones[currentIndex].isOnTarget(target))
        {
            globalBestIndex = currentIndex;
            return;
        }

        if (drones[currentIndex].getLocation().euclideanDistance(target) <
            drones[globalBestIndex].getLocation().euclideanDistance(target))
        {
            globalBestIndex = currentIndex; // Update the global best index
        }
    }
}

void Simulation::updatePersonalBest(const size_t currentIndex) const
{
    if (drones[currentIndex].getLocation().euclideanDistance(target) <
        drones[currentIndex].getPB().euclideanDistance(target))
    {
        drones[currentIndex].setPB(drones[currentIndex].getLocation());
    }
}

const DirectionalVector& Simulation::getTarget() const
{
    return target;
}

void Simulation::run()
{
    // std::cout << "Initial state: " << std::endl;
    // printState();
    for (unsigned int step = 0; step < iterations; ++step)
    {
        for (size_t i = 0; i < AMOUNT; ++i)
        {
            GridIndex oldIndex = getGridIndex(drones[i].getLocation());

            drones[i].move(drones[globalBestIndex]);

            GridIndex newIndex = getGridIndex(drones[i].getLocation());

            if (oldIndex != newIndex)
            {
                --forest[oldIndex.x][oldIndex.y];
                ++forest[newIndex.x][newIndex.y];
            }

            updatePersonalBest(i);

            if (drones[i].isOnTarget(target))
            {
                // std::cout << "Step " << step + 1 << std::endl;
                // printState();
                // std::cout << "Drone " << drones[i].getID() << " reached the target!" << std::endl;
                return; // End simulation early
            }
        }

        updateGlobalBest();

        for (int i = 0; i < AMOUNT; ++i)
        {
            drones[i].updateVelocity(drones[globalBestIndex]);
        }
        // std::cout << "Step " << step + 1 << std::endl;
        // printState();
    }

    // std::cout << "Simulation ended: Not all drones reached the target." << std::endl;
}

// Print the state of the simulation
void Simulation::printState() const
{
    std::cout << "Target: " << target << std::endl;
    for (size_t i = 0; i < AMOUNT; ++i)
    {
        std::cout << drones[i] << std::endl;
    }
    std::cout << "Global best: " << drones[globalBestIndex] << std::endl;
}

// // Save the state to a file, commented because I think mine's better
// void Simulation::saveState(const std::string& outputFile) const
// {
//     std::ofstream file(outputFile);
//     if (not file.is_open())
//     {
//         std::cerr << "Error: Could not open file " << outputFile << " for writing." << std::endl;
//         return;
//     }
//
//     file << "Final Simulation State:" << std::endl;
//     file << "Target: " << target << std::endl;
//     for (size_t i = 0; i < AMOUNT; ++i)
//     {
//         file << "Drone " << drones[i].getID() << " at " << drones[i].getLocation()
//              << " with speed " << drones[i].getVelocity() << std::endl;
//     }
//
//     file.close();
//     std::cout << "Simulation state saved to " << outputFile << std::endl;
// }

void Simulation::saveState(const std::string& outputFile) const
{
    std::ofstream file(outputFile);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << outputFile << std::endl;
        return;
    }

    file << iterations << std::endl;

    // file << std::defaultfloat << std::setprecision(3);

    for (size_t i = 0; i < AMOUNT; ++i)
    {
        file << drones[i].getLocation() << std::endl;
    }

    file.close();
}

GridIndex Simulation::getGridIndex(const DirectionalVector& position)
{
    const int gridX = static_cast<int>(position.getX());
    const int gridY = static_cast<int>(position.getY());
    return GridIndex(gridX, gridY);
}

unsigned int Simulation::operator()(const unsigned int x, const unsigned int y) const
{
    return forest[x][y].get_dronesCount();
}
