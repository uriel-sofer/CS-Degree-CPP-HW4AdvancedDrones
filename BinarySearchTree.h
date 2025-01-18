#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

/**
 *
 * @tparam T T must implement: <br>
 * - "<, =, >" for equality evaluations <br>
 * - "<<" for ostream usage.
 */
template<class T>
class BinarySearchTree {
private:
    T value;
    int height; // How many junctions are below
    int tree_size; // amount of junctions in the tree

    BinarySearchTree *left;
    BinarySearchTree *right;

    void updateHeightAndSize()
    {
        const int leftHeight = left ? left->height : -1;
        const int rightHeight = right ? right->height : -1;
        height = 1 + max(leftHeight, rightHeight);

        const int leftSize = left ? left->tree_size : 0;
        const int rightSize = right ? right->tree_size : 0;
        tree_size = 1 + leftSize + rightSize;
    }

    static const int &max(const int &a, const int &b)
    {
        return a > b ? a : b;
    }

    static const int &min(const int &a, const int &b)
    {
        return a < b ? a : b;
    }

public:
    BinarySearchTree() : height(0), tree_size(1), left(nullptr), right(nullptr)
    {}

    explicit BinarySearchTree(T value) : value(value), height(0), tree_size(1)
    {
        left = nullptr;
        right = nullptr;
    }

    BinarySearchTree(T value, BinarySearchTree left, BinarySearchTree right) : value(value), height(0), tree_size(1),
                                                                               left(left), right(right)
    {
        updateHeightAndSize();
    }

    ~BinarySearchTree()
    {
        clear();
    }

    T getValue() const
    {
        return value;
    }

    int getHeight() const
    {
        return height;
    }

    int size() const
    {
        return tree_size;
    }

    BinarySearchTree get_left() const;

    BinarySearchTree get_right() const;

    /**
     * Attempts to insert element to tree. No duplicates.
     * @param element to be inserted into the tree
     */
    void insert(const T &element);

    /**
     * Searches if element is in the tree
     * @param element element to search
     * @return true if found
     */
    T *search(const T &element);

    /**
     *
     * @return min element in the tree
     */
    T *min();

    /**
     *
     * @return max element in the tree
     */
    T *max();

    /**
     * Attempts to remove an element from the tree
     * @param element element to be removed from the tree
     */
    void remove(const T &element);

    /**
     * Clears the tree of all elements
     */
    void clear();

    /**
     * Prints the tree (using <<) Inorder.
     */
    void print() const;
};

template<class T>
BinarySearchTree<T> BinarySearchTree<T>::get_left() const
{
    return left;
}

template<class T>
BinarySearchTree<T> BinarySearchTree<T>::get_right() const
{
    return right;
}

template<class T>
void BinarySearchTree<T>::insert(const T &element)
{
    if (!element)
    {
        return; // Don't insert nullptr
    }

    if (!value)
    {
        value = element; // Initialize root value
        return;
    }

    if (*element == *value)
    {
        // Overwrite the existing value
        *value = *element; // Update the value itself (for non-pointer types)
        return;
    }

    if (*element < *value)
    {
        if (!left)
        {
            left = new BinarySearchTree(element);
        } else
        {
            left->insert(element);
        }
    } else
    {
        if (!right)
        {
            right = new BinarySearchTree(element);
        } else
        {
            right->insert(element);
        }
    }
    updateHeightAndSize();
}

template<class T>
T *BinarySearchTree<T>::search(const T &element)
{
    if (value == element)
        return &value;

    if (element < value)
        return left ? left->search(element) : nullptr;

    if (element > value)
        return right ? right->search(element) : nullptr;

    return nullptr;
}

template<class T>
T *BinarySearchTree<T>::min()
{
    if (left)
        return left->min();
    return &value; // If no left child, this node is the smallest
}


template<class T>
T *BinarySearchTree<T>::max()
{
    if (right)
        return right->max();
    return &value; // If no right child, this node is the biggest
}

template<class T>
void BinarySearchTree<T>::remove(const T &element)
{
    if (size() == 0)
        return;

    if (value == element)
    {
        // Leaf case
        if (left == nullptr and right == nullptr)
        {
            tree_size = 0;
            height = 0;
            return;
        }

        // One child cases
        // left child
        if (left != nullptr && right == nullptr)
        {
            *this = *left;
            return;
        }

        // right child
        if (left == nullptr && right != nullptr)
        {
            *this = *right;
            return;
        }

        // Two children cases
        T successorValue = *right->min();
        value = successorValue;
        right->remove(successorValue);
    } else
    {
        if (element < value)
        {
            if (left)
                left->remove(element);
        } else
        {
            if (right)
                right->remove(element);
        }
    }

    updateHeightAndSize();
}

template<class T>
void BinarySearchTree<T>::clear()
{
    if (left)
    {
        left->clear();
        delete left;
        left = nullptr;
    }
    if (right)
    {
        right->clear();
        delete right;
        right = nullptr;
    }
    height = 0;
    tree_size = 0;
}

template<class T>
void BinarySearchTree<T>::print() const
{
    if (left)
        left->print();

    if (tree_size != 0)
        std::cout << *value << " ";

    if (right)
        right->print();
}

#endif //BINARY_SEARCH_TREE_H
