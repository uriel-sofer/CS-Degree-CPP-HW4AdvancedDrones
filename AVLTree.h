#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

template<class T>
class AVLTree {
private:
    T value;
    int height; // How many junctions are below
    int tree_size; // Amount of junctions in the tree

    AVLTree *left;
    AVLTree *right;

    void updateHeightAndSize()
    {
        const int leftHeight = left ? left->height : -1;
        const int rightHeight = right ? right->height : -1;
        height = 1 + max(leftHeight, rightHeight);

        const int leftSize = left ? left->tree_size : 0;
        const int rightSize = right ? right->tree_size : 0;
        tree_size = 1 + leftSize + rightSize;
    }

    static int max(const int a, const int b)
    {
        return a > b ? a : b;
    }

    static int min(const int a, const int b)
    {
        return a < b ? a : b;
    }

    int getBalanceFactor() const
    {
        const int leftHeight = left ? left->height : -1;
        const int rightHeight = right ? right->height : -1;
        return leftHeight - rightHeight;
    }

    AVLTree *rotateRight()
    {
        AVLTree *newRoot = left;
        AVLTree *temp = newRoot->right;

        newRoot->right = this;
        left = temp;

        updateHeightAndSize();
        newRoot->updateHeightAndSize();
        return newRoot;
    }

    AVLTree *rotateLeft()
    {
        AVLTree *newRoot = right;
        AVLTree *temp = newRoot->left;

        newRoot->left = this;
        right = temp;

        updateHeightAndSize();
        newRoot->updateHeightAndSize();
        return newRoot;
    }

    AVLTree *balance()
    {
        updateHeightAndSize();

        const int balanceFactor = getBalanceFactor();

        // Left heavy
        if (balanceFactor > 1)
        {
            if (left && left->getBalanceFactor() < 0) {
                left = left->rotateLeft(); // Left-Right Case
            }
            return rotateRight(); // Left-Left Case
        }

        // Right heavy
        if (balanceFactor < -1)
        {
            if (right && right->getBalanceFactor() > 0) {
                right = right->rotateRight(); // Right-Left Case
            }
            return rotateLeft(); // Right-Right Case
        }

        return this; // Balanced
    }

public:
    AVLTree() : height(0), tree_size(1), left(nullptr), right(nullptr)
    {}

    explicit AVLTree(T value) : value(value), height(0), tree_size(1)
    {
        left = nullptr;
        right = nullptr;
    }

    T* search(const T& element)
    {
        if (value == element)
            return &value;

        if (element < value)
            return left ? left->search(element) : nullptr;

        if (element > value)
            return right ? right->search(element) : nullptr;

        return nullptr;
    }

    void insert(const T &element)
    {
        if (element < value)
        {
            if (!left)
                left = new AVLTree(element);
            else
                left->insert(element);
        }
        else if (element > value)
        {
            if (!right)
                right = new AVLTree(element);
            else
                right->insert(element);
        }
        else
        {
            value = element; // Override if exists
        }

        *this = *balance();
    }

    void remove(const T &element)
    {
        if (element < value)
        {
            if (left)
                left->remove(element);
        }
        else if (element > value)
        {
            if (right)
                right->remove(element);
        }
        else
        {
            // Node to be deleted
            if (!left || !right)
            {
                AVLTree *temp = left ? left : right;
                if (temp)
                    *this = *temp; // Replace with non-null child
                else
                    tree_size = 0; // Leaf node
                return;
            }

            // Two children: Get in-order successor
            T successorValue = *right->min();
            value = successorValue;
            right->remove(successorValue);
        }

        if (tree_size > 0)
            *this = *balance();
    }

    T* min()
    {
        if (left)
            return left->min();
        return &value;
    }

    T* max()
    {
        if (right)
            return right->max();
        return &value;
    }

    void print() const
    {
        if (left)
            left->print();

        if (tree_size > 0)
            std::cout << value << " ";

        if (right)
            right->print();
    }
};



#endif //AVLTREE_H
