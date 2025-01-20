#include <fstream>
#include <iostream>
#include <ctime>

#include "FileHandler.h"
#include "TreeSim.h"

// Function to log errors to a file
void logError(const std::string& message)
{
    // Write only if opened
    if (std::ofstream logFile("error.log", std::ios::trunc); logFile.is_open())
        logFile << message << std::endl;
}

// Function to parse command-line arguments
void parseArguments(const int argc, char* argv[], int& seed)
{
    // Wrong arguments
    if (not(argc >= 4 and argc <= 5))
        throw std::invalid_argument("Usage: " + std::string(argv[0]) +
            " <config_file> <init_file> <output_file> Optional: <seed>");

    // Seed parsing
    if (argc == 5)
        seed = std::strtol(argv[4], nullptr, 10);
    else
        seed = static_cast<int>(std::time(nullptr));
}

int main(int argc, char* argv[])
{
    int seed = 0;

    // Parse arguments and initialize the seed
    try
    {
        parseArguments(argc, argv, seed);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Error; invalid input" << std::endl;
        logError(e.what());
        return 1;
    }

    std::srand(seed);

    // Parse config and init/locations files
    Config config;
    Init init;

    try
    {
        config = ConfigParser(argv[1]);
        init = InitParser(argv[2]);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error; invalid input" << std::endl;
        logError(e.what());
        return 1;
    }

    // Validate configuration and initialization
    if (config.iterations < 0 || init.initialLocations.getSize() == 0)
    {
        std::cerr << "Error; invalid input" << std::endl;
        logError("Invalid configuration or initialization");
        return 1;
    }

    // Run the simulation
    TreeSim simulation(config, init);
    simulation.run();
    simulation.saveState(argv[3]); // Output file

    return 0;
}
