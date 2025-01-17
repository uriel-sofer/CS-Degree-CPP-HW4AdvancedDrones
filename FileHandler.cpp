#include "FileHandler.h"
#include <fstream>

Config ConfigParser(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (not file.is_open())
    {
        //std::cerr << "Error: Could not open file " << filePath << std::endl;
        std::cerr << "Error; invalid input" << std::endl;
        return Config();
    }

    double x, y;
    unsigned int iterations;

    // Wrong file format will trigger an error here
    if (not(file >> x >> y >> iterations))
    {
        //std::cerr << "Error: Invalid format in config file" << std::endl;
        std::cerr << "Error; invalid input" << std::endl;
        return Config(); // "default" object is treated as an error in the main
    }
    return Config(Point(x, y), iterations);
}

Init InitParser(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (not file.is_open())
    {
        //std::cerr << "Error: Could not open file " << filePath << std::endl;
        std::cerr << "Error; invalid input" << std::endl;
        return Init();
    }

    Init init;
    double x, y, speed_x, speed_y;
    int drones_amount = 0;

    // Read drones amount from the first line
    if (not (file >> drones_amount) || drones_amount < 0)
    {
        //std::cerr << "Error: Invalid number of drones in the init file" << std::endl;
        std::cerr << "Error; invalid input" << std::endl;
        return Init();
    }

    init.dronesAmount = drones_amount;

    for (int i = 0; i < drones_amount; ++i)
    {
        // Wrong file format will trigger an error here
        if (not (file >> x >> y >> speed_x >> speed_y))
        {
            //std::cerr << "Error: Invalid format on line " << i + 2 << " in init file" << std::endl;
            return Init(); // "default" object is treated as an error in the main
        }

        init.initialLocations.push_back(DirectionalVector(x, y));
        init.speeds.push_back(DirectionalVector(speed_x, speed_y));
    }

    return init;
}

