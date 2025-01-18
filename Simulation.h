#ifndef SIMULATION_H
#define SIMULATION_H

#include "DirectionalVector.h"
#include "Drone.h"
#include "FileHandler.h"
#include "ForestIndex.h"
#include "BinarySearchTree.h"

class Simulation {
private:
    DirectionalVector target; // Target location
    const size_t AMOUNT; // Amount of drones in the simulation
    Drone** drones; // The array of the drones

    BinarySearchTree<Drone*> dronesTree;

    const unsigned int iterations; // Number of simulation steps
    size_t globalBestIndex; // Index of the global best drone
    ForestIndex** forest;

public:
    Simulation(const Config& config, const Init& init);
    ~Simulation();
    void run(); // Activates the simulation, start iterating
    void updateGlobalBest();
    void updatePersonalBest(size_t currentIndex) const; // Update the PB for drones[currentIndex]
    void printState() const; // Prints the state of the simulation, where each drone is and what are its stats
    void saveState(const std::string& outputFile) const; // Saves the final state to a file
    static GridIndex getGridIndex(const DirectionalVector& position); // Converts the DirectionalVector to an GridIndex

    const DirectionalVector& getTarget() const;

    void printDronesTree();

    unsigned int operator()(unsigned int x, unsigned int y) const; // Returns amount of drones in x,y
};

#endif
