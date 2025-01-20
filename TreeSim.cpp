#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "TreeSim.h"
#include "SingleRotor.h"
#include "MultiRotor.h"
#include "FixedWing.h"
#include "HybridDrone.h"

// Static function to delete a drone
void TreeSim::deleteDrone(const Drone* drone)
{
    delete drone;
}

// Static function to print a drone
void TreeSim::printDrone(const Drone* drone)
{
    std::cout << *drone;
}


TreeSim::TreeSim(const Config& config, const Init& init)
    : target(config.target), iterations(config.iterations), globalBestID(0)
{
    for (int i = 0; i < init.dronesAmount; ++i)
    {
        Drone* drone = nullptr;
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


void TreeSim::updatePersonalBest(Drone* drone) const
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
    Drone* globalBest = dronesTree.findGlobalBest(target);
    if (globalBest)
    {
        globalBestID = globalBest->getID();
    }
}

// Convert a position to a grid index
GridIndex TreeSim::getGridIndex(const DirectionalVector& position)
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
        dronesTree.traverseInOrder([this, step](Drone* drone)
        {
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
        dronesTree.traverseInOrder([this](Drone* drone)
        {
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

/**
 * Formats a double in the desired format
 * - Two digits after the decimal point
 * - ignore trailing zeroes
 * @param val double to be formatted
 * @return a string matching the format:
 */
std::string formatDouble(const double val)
{
    // Get only two after the decimal point
    std::ostringstream os;
    os << std::fixed << std::setprecision(2) << val;
    std::string result = os.str();

    if (result.find('.') != std::string::npos) // Check if the number contains a decimal point
    {
        // Remove trailing zeros from the fractional part
        result.erase(result.find_last_not_of('0') + 1, std::string::npos);
        if (result.back() == '.') // If only decimal point left, remove
        {
            result.pop_back();
        }
    }

    return result;
}

void TreeSim::saveState(const std::string& outputFile) const
{
    std::ofstream file(outputFile);
    if (!file.is_open())
    {
        std::cerr << "Error; invalid input" << std::endl;
        throw std::invalid_argument("Could not open" + outputFile +  "file " + outputFile);
    }

    file << iterations << std::endl;

    dronesTree.traverseInOrder([&file](const Drone* drone)
    {
        file << drone->getDroneType() << " ";
        file << formatDouble(drone->getLocation().getX()) << " "
            << formatDouble(drone->getLocation().getY()) << std::endl;
    });

    file.close();
}
