#include "FileHandler.h"
#include <fstream>

/**
 * Validates the limits (x_min < x_max and y_min < y_max)) , if the limits are invalid sets config to be the default object (therefore an error)
 * @param limits limits array
 * @return true for <b>invalid</b> limits
 */
bool validateLimits(int limits[4])
{
    if (limits[0] > limits[2])
    {
        throw std::runtime_error(
            "Error: Invalid x limits in config: x_min (" + std::to_string(limits[0]) +
            ") > x_max (" + std::to_string(limits[2]) + ")"
        );
    }

    if (limits[1] > limits[3])
    {
        throw std::runtime_error(
            "Error: Invalid y limits in config: y_min (" + std::to_string(limits[1]) +
            ") > y_max (" + std::to_string(limits[3]) + ")"
        );
    }

    return false; // Limits are valid
}


/**
 * parses the config file and fills it with the relevant data,
 * "default" object is treated as an error in the main
 * @param filePath path to the config file
 * @return Config object with the relevant data, or a default object (treated as an error)
 */
Config ConfigParser(const std::string &filePath)
{
    Config config;
    std::ifstream file(filePath);
    if (not file.is_open())
    {
        //std::cerr << "Error: Could not open file " << filePath << std::endl;
        std::cerr << "Error; invalid input" << std::endl;
        throw std::runtime_error("Could not open file");
    }

    // Read xmin, ymin, xmax, ymax (the first line)
    int limits[4];
    for (int i = 0; i < 4; ++i)
    {
        if (not(file >> limits[i]))
        {
            //std::cerr << "Error: Unable to read limit " << i + 1 << " from config" << std::endl;
            throw std::runtime_error("Unable to read limit " + std::to_string(i + 1));
        }
    }

    // Validate xmin <= xmax and ymin <= ymax
    if (validateLimits(limits))
        throw std::runtime_error("limit values are invalid");

    Point::setLimits(limits);

    double target_x, target_y;
    unsigned int iterations;

    // Wrong file format will trigger an error here
    if (not(file >> target_x >> target_y >> iterations))
    {
        //std::cerr << "Error: Invalid format in config file" << std::endl;
        std::cerr << "Error; invalid input" << std::endl;
        throw std::runtime_error("Invalid format in config file");
    }

    // Validate target's coordinates
    if (not Point::validateCoordinates(target_x, target_y))
    {
        //std::cerr << "Error: Invalid target's coordinates in config file" << std::endl;
        std::cerr << "Error; invalid input" << std::endl;
        throw std::runtime_error("Invalid coordinates in config file");
    }

    config.target = DirectionalVector(Point(target_x, target_y));
    config.iterations = iterations;
    return config;
}

Init InitParser(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (not file.is_open())
    {
        //std::cerr << "Error: Could not open file " << filePath << std::endl;
        std::cerr << "Error; invalid input" << std::endl;
        throw std::runtime_error("Could not open file");
    }

    Init init;
    int drones_amount = 0;

    // Read drones amount from the first line
    if (not(file >> drones_amount) || drones_amount < 0)
    {
        //std::cerr << "Error: Invalid number of drones in the init file" << std::endl;
        std::cerr << "Error; invalid input" << std::endl;
        throw std::runtime_error("Invalid format in config file");
    }

    init.dronesAmount = drones_amount;
    double x, y, speed_x, speed_y;
    char droneType;

    for (int i = 0; i < drones_amount; ++i)
    {
        // Wrong file format will trigger an error here
        if (not(file >> droneType >> x >> y >> speed_x >> speed_y))
        {
            //std::cerr << "Error: Invalid format on line " << i + 2 << " in init file" << std::endl;
            std::cerr << "Error; invalid input" << std::endl;
            throw std::runtime_error("Invalid format in config file" + std::to_string(i + 1));
        }

        if (droneType != 'S' and droneType != 'M' and droneType != 'W' and droneType != 'H')
        {
            //std::cerr << "Error: Invalid drone type on line " << i + 2 << " in init file" << std::endl;
            std::cerr << "Error; invalid input" << std::endl;
            throw std::runtime_error("Invalid format in config file" + std::to_string(i + 1));
        }

        init.initialLocations.push_back(DirectionalVector(x, y));
        init.speeds.push_back(DirectionalVector(speed_x, speed_y));
        init.dronesTypes.push_back(droneType);
    }

    return init;
}
