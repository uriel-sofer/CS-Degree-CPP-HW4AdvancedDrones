#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <limits>

#include "DirectionalVector.h"

template<class T>
class BinarySearchTree {
private:
    T value; // Node value
    BinarySearchTree* left;
    BinarySearchTree* right;

public:
    BinarySearchTree() : value(nullptr), left(nullptr), right(nullptr) {}

    explicit BinarySearchTree(T val) : value(val), left(nullptr), right(nullptr) {}

    ~BinarySearchTree() {
        clear();
    }

    // Insert a value into the tree
    void insert(const T& newValue) {
        if (!value) {
            value = newValue;
            return;
        }

        if (*newValue < *value) {
            if (!left) left = new BinarySearchTree(newValue);
            else left->insert(newValue);
        } else if (*newValue > *value) {
            if (!right) right = new BinarySearchTree(newValue);
            else right->insert(newValue);
        } else {
            value = newValue; // Overwrite if equal
        }
    }

    // Traverse the tree in-order with a callable object
    template<typename Callable>
    void traverseInOrder(Callable process) const {
        if (left) left->traverseInOrder(process);
        if (value) process(value);
        if (right) right->traverseInOrder(process);
    }

    // Find the drone closest to the target
    T findGlobalBest(const DirectionalVector& target) const {
        T best = nullptr;
        double bestDistance = std::numeric_limits<double>::max();

        inOrderFindBest(this, target, best, bestDistance);
        return best;
    }

    // Clear the tree and free memory
    void clear() {
        if (left) {
            left->clear();
            delete left;
            left = nullptr;
        }
        if (right) {
            right->clear();
            delete right;
            right = nullptr;
        }
        value = nullptr;
    }

private:
    // Helper for in-order traversal to find the global best
    static void inOrderFindBest(const BinarySearchTree* tree, const DirectionalVector& target, T& best, double& bestDistance) {
        if (!tree || !tree->value) return;

        // Visit left subtree
        inOrderFindBest(tree->left, target, best, bestDistance);

        // Check current node
        double currentDistance = tree->value->getLocation().euclideanDistance(target);
        if (currentDistance < bestDistance) {
            bestDistance = currentDistance;
            best = tree->value;
        }

        // Visit right subtree
        inOrderFindBest(tree->right, target, best, bestDistance);
    }
};

#endif // BINARY_SEARCH_TREE_H