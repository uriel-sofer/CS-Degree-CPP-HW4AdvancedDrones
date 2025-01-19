#include "TreeSim.h"
#include <iostream>
#include <fstream>
#include <iomanip>

// Static function to delete a drone
void TreeSim::deleteDrone(const Drone *drone)
{
    delete drone;
}

// Static function to print a drone
void TreeSim::printDrone(const Drone *drone)
{
    std::cout << *drone;
}


TreeSim::TreeSim(const Config &config, const Init &init)
    : target(config.target), iterations(config.iterations), globalBestID(0)
{
    for (size_t i = 0; i < init.dronesAmount; ++i)
    {
        Drone *drone = nullptr;
        switch (init.dronesTypes[i])
        {
            case 'S':
                drone = new SingleRotor(init.initialLocations[i], init.speeds[i], target, 'S');
                break;
            case 'M':
                drone = new MultiRotor(init.initialLocations[i], init.speeds[i], target, 'M');
                break;
            case 'W':
                drone = new FixedWing(init.initialLocations[i], init.speeds[i], target, 'W');
                break;
            case 'H':
                drone = new HybridDrone(init.initialLocations[i], init.speeds[i], target, 'H');
                break;
            default:
                throw std::invalid_argument("Unknown drone type");
        }
        dronesTree.insert(drone);
        updatePersonalBest(drone);
    }
    updateGlobalBest();
}


TreeSim::~TreeSim()
{
    dronesTree.traverseInOrder(deleteDrone); // Use static delete function
    dronesTree.clear();
}


void TreeSim::updatePersonalBest(Drone *drone) const
{
    if (drone->getLocation().euclideanDistance(target) <
        drone->getPB().euclideanDistance(target))
    {
        drone->setPB(drone->getLocation());
    }
}

// Update the global best drone
void TreeSim::updateGlobalBest()
{
    Drone *globalBest = dronesTree.findGlobalBest(target);
    if (globalBest)
    {
        globalBestID = globalBest->getID();
    }
}

// Convert a position to a grid index
GridIndex TreeSim::getGridIndex(const DirectionalVector &position)
{
    const int gridX = static_cast<int>(position.getX());
    const int gridY = static_cast<int>(position.getY());
    return GridIndex(gridX, gridY);
}

// Run the simulation
void TreeSim::run()
{
    // std::cout << "Initial state: " << std::endl;
    // printState();

    for (unsigned int step = 0; step < iterations; ++step)
    {
        /*
         * Move loop
         * Here I used a C++ lambda function.
         * I wanted to do all of these to each of the drones, and not just move
         */
        dronesTree.traverseInOrder([this, step](Drone *drone) {
            drone->move(*(dronesTree.findGlobalBest(target)));
            updatePersonalBest(drone);

            if (drone->isOnTarget(target))
            {
                std::cout << "Step " << step + 1 << std::endl;
                printState();
                std::cout << "Drone " << drone->getID() << " reached the target!" << std::endl;
            }
        }); // Pretty long "one line"

        updateGlobalBest();

        // Update velocity loop
        dronesTree.traverseInOrder([this](Drone *drone) {
            drone->updateVelocity(*dronesTree.findGlobalBest(target));
        });

        // std::cout << std::endl << "Step " << step + 1 << std::endl;
        // printState();
    }
}

// Print the current state of the simulation
void TreeSim::printState() const
{
    std::cout << "Target: " << target << std::endl;
    dronesTree.traverseInOrder(printDrone); // Use static print function
    std::cout << "Global best ID: " << globalBestID << std::endl;
}

// Save the simulation state to a file
void TreeSim::saveState(const std::string &outputFile) const
{
    std::ofstream file(outputFile);
    if (!file.is_open())
    {
        std::cerr << "Error; Invalid input";
        throw std::invalid_argument("Could not open file " + outputFile);
        // std::cerr << "Error: Could not open file " << outputFile << std::endl;
        // return;
    }

    file << iterations << std::endl;
    file << std::defaultfloat << std::setprecision(3);

    dronesTree.traverseInOrder([&file](const Drone *drone) {
        file << drone->getDroneType() << " " << drone->getLocation() << std::endl;
    });

    file.close();
}
