#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include "Point.h"
#include "Vector.h"
#include "DirectionalVector.h"

/**
 * Struct to hold the data for the configuration file.
 * Holds the target and iterations
 */
struct Config {
    DirectionalVector target;
    unsigned int iterations;

    Config(const Point& target, const unsigned int iterations)
        : target(target), iterations(iterations) {}

    Config() : target(Point()), iterations(0) {}
};

/**
 * Struct to hold the data for the initialization file
 */
struct Init {
    Vector<DirectionalVector> initialLocations;
    Vector<DirectionalVector> speeds;
    int dronesAmount = 0;

    Init() = default; // Does it count as an object? Anyway default is enough
};

/**
* Parses the config.dat file
*/
Config ConfigParser(const std::string& filePath);

/**
* Parses the init.dat file
*/
Init InitParser(const std::string& filePath);

#endif
