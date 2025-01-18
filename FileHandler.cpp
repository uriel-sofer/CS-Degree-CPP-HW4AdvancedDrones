#include "FileHandler.h"
#include <fstream>

/**
 * Validates the limits (x_min < x_max and y_min < y_max)) , if the limits are invalid sets config to be the default object (therefore an error)
 * @param limits limits array
 * @param config the config object we parse into
 * @return true for <b>invalid</b> limits
 */
bool validateLimits(int limits[4], Config &config)
{
    if (limits[0] > limits[2])
    {
        std::cerr << "Error: Invalid x limits in config: x_min (" << limits[0]
                << ") > x_max (" << limits[2] << ")" << std::endl;
        config = Config();
        return true;
    }

    if (limits[1] > limits[3])
    {
        std::cerr << "Error: Invalid y limits in config: y_min (" << limits[1]
                << ") > y_max (" << limits[3] << ")" << std::endl;
        config = Config();
        return true;
    }
    return false;
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
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        //std::cerr << "Error; invalid input" << std::endl;
        return config;
    }

    // Read xmin, ymin, xmax, ymax (the first line)
    int limits[4];
    for (int i = 0; i < 4; ++i)
    {
        if (not(file >> limits[i]))
        {
            std::cerr << "Error: Unable to read limit " << i + 1 << " from config" << std::endl;
            return config;
        }
    }

    // Validate xmin <= xmax and ymin <= ymax
    if (validateLimits(limits, config))
        return config;

    Point::setLimits(limits);

    double target_x, target_y;
    unsigned int iterations;

    // Wrong file format will trigger an error here
    if (not(file >> target_x >> target_y >> iterations))
    {
        std::cerr << "Error: Invalid format in config file" << std::endl;
        //std::cerr << "Error; invalid input" << std::endl;
        return config;
    }

    // Validate target's coordinates
    if (not Point::validateCoordinates(target_x, target_y))
        std::cerr << "Error: Invalid target's coordinates in config file" << std::endl;

    config.target = DirectionalVector(Point(target_x, target_y));
    config.iterations = iterations;
    return config;
}

Init InitParser(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (not file.is_open())
    {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        //std::cerr << "Error; invalid input" << std::endl;
        return Init();
    }

    Init init;
    int drones_amount = 0;

    // Read drones amount from the first line
    if (not(file >> drones_amount) || drones_amount < 0)
    {
        std::cerr << "Error: Invalid number of drones in the init file" << std::endl;
        //std::cerr << "Error; invalid input" << std::endl;
        return Init();
    }

    init.dronesAmount = drones_amount;
    double x, y, speed_x, speed_y;
    char droneType;

    for (int i = 0; i < drones_amount; ++i)
    {
        // Wrong file format will trigger an error here
        if (not(file >> droneType >> x >> y >> speed_x >> speed_y))
        {
            std::cerr << "Error: Invalid format on line " << i + 2 << " in init file" << std::endl;
            return Init(); // "default" object is treated as an error in the main
        }

        if (droneType != 'S' and droneType != 'M' and droneType != 'W' and droneType != 'H')
        {
            std::cerr << "Error: Invalid drone type on line " << i + 2 << " in init file" << std::endl;
        }

        init.initialLocations.push_back(DirectionalVector(x, y));
        init.speeds.push_back(DirectionalVector(speed_x, speed_y));
        init.dronesTypes.push_back(droneType);
    }

    return init;
}
