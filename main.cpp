#include <fstream>
#include <iostream>

#include "FileHandler.h"
#include "TreeSim.h"


int main(int argc, char *argv[])
{
    // 3 arguments without seed, 4 arguments with the seed, everything else is wrong
    // Increment by one because program name is also an argument
    if (not(argc >= 4 and argc <= 5))
    {
        std::cerr << "Usage: " << argv[0] << " <config_file> <init_file> <output_file> Optional: <seed>" << std::endl;
        //std::cerr << "Error; invalid input" << std::endl;
        return 1;
    }

    int seed = 0;
    if (argc == 5)
    {
        seed = std::strtol(argv[4], nullptr, 10);
    }

    std::srand(seed != 0 ? seed : static_cast<unsigned int>(std::time(nullptr)));

    // Parse through the files
    Config config;
    Init init;


    try
    {
        config = ConfigParser(argv[1]);
        init = InitParser(argv[2]);
    } catch (std::runtime_error &e)
    {
        // Log the error to a file
        std::ofstream logFile("error.log", std::ios::trunc); // Open in append mode
        if (logFile.is_open())
        {
            logFile << e.what() << std::endl;
            logFile.close();
        } else
        {
            std::cerr << "Unable to open log file for writing." << std::endl;
            return 1;
        }

    }


    if (config.iterations < 0 || init.initialLocations.getSize() == 0)
    {
        //std::cerr << "Error: Invalid configuration or initialization\n";
        std::cerr << "Error; invalid input" << std::endl;
        return 1;
    }

    try
    {
        TreeSim simulation(config, init);
        simulation.run();
        simulation.saveState(argv[3]); // Output file
    } catch (...)
    {}

    return 0;
}
