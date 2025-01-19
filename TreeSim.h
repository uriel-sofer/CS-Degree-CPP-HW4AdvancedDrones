#ifndef TREE_SIM_H
#define TREE_SIM_H

#include "BinarySearchTree.h"
#include "DirectionalVector.h"
#include "Drone.h"
#include "SingleRotor.h"
#include "MultiRotor.h"
#include "FixedWing.h"
#include "HybridDrone.h"
#include "ForestIndex.h"
#include "FileHandler.h"

class TreeSim {
private:
    BinarySearchTree<Drone*> dronesTree;
    DirectionalVector target;
    unsigned int iterations;
    unsigned int globalBestID;

    void updateGlobalBest();
    void updatePersonalBest(Drone* drone) const;
    static GridIndex getGridIndex(const DirectionalVector& position);

    // Static member functions for tree traversal
    static void deleteDrone(const Drone* drone);
    static void printDrone(const Drone* drone);

public:
    TreeSim(const Config& config, const Init& init);
    ~TreeSim();

    void run();
    void printState() const;
    void saveState(const std::string& outputFile) const;
};

#endif // TREE_SIM_H