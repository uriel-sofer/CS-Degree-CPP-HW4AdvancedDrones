#include "Simulation.h"
#include "FileHandler.h"
#include <iostream>

#include "AVLTree.h"

// void testBSTInteger()
// {
//     BinarySearchTree<int> bst;
//
//     // Test insertion
//     bst.insert(10);
//     bst.insert(5);
//     bst.insert(15);
//     bst.insert(3);
//     bst.insert(7);
//     bst.insert(12);
//     bst.insert(18);
//
//     std::cout << "Tree after insertion: ";
//     bst.print();
//     std::cout << "\n";
//
//     // Test search
//     int searchValue = 7;
//     if (bst.search(searchValue)) {
//         std::cout << "Found: " << searchValue << "\n";
//     } else {
//         std::cout << "Not found: " << searchValue << "\n";
//     }
//
//     // Test minimum and maximum
//     std::cout << "Minimum value: " << *bst.min() << "\n";
//     std::cout << "Maximum value: " << *bst.max() << "\n";
//
//     // Test removal
//     bst.remove(5);
//     std::cout << "Tree after removing 5: ";
//     bst.print();
//     std::cout << "\n";
//
//     bst.remove(10);
//     std::cout << "Tree after removing 10: ";
//     bst.print();
//     std::cout << "\n";
//
//     // Test clearing the tree
//     bst.clear();
//     std::cout << "Tree after clearing: ";
//     bst.print();
//     std::cout << "\n";
// }

int main(int argc, char* argv[])
{
    // testBSTInteger();


    // Handle wrong arguments
    if (not (argc >= 4 and argc <= 5))
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
    const Config config = ConfigParser(argv[1]);
    const Init init = InitParser(argv[2]);

    if (config.iterations < 0 || init.initialLocations.getSize() == 0)
    {
        std::cerr << "Error: Invalid configuration or initialization\n";
        //std::cerr << "Error; invalid input" << std::endl;
        return 1;
    }

    Simulation simulation(config, init);
    simulation.run();
    simulation.saveState(argv[3]); // Output file

    return 0;
}
