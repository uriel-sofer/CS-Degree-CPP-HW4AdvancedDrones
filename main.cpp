#include "Simulation.h"
#include "FileHandler.h"
#include <iostream>

int main(int argc, char* argv[])
{
    // Handle wrong arguments
    if (argc != 4)
    {
        //std::cerr << "Usage: " << argv[0] << " <config_file> <init_file> <output_file>" << std::endl;
        std::cerr << "Error; invalid input" << std::endl;
        return 1;
    }

    // Parse through the files
    const Config config = ConfigParser(argv[1]);
    const Init init = InitParser(argv[2]);

    if (config.iterations < 0 || init.initialLocations.getSize() == 0)
    {
        //std::cerr << "Error: Invalid configuration or initialization\n";
        std::cerr << "Error; invalid input" << std::endl;
        return 1;
    }

    Simulation simulation(config, init);
    simulation.run();
    simulation.saveState(argv[3]); // Output file

    return 0;
}
