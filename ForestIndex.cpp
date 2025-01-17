#include "ForestIndex.h"

// Default Constructor
ForestIndex::ForestIndex() : index(GridIndex()), dronesCount(0) {}

// Parameterized Constructor with coordinates
ForestIndex::ForestIndex(int x, int y) : index(GridIndex(x, y)), dronesCount(0) {}

// Parameterized Constructor with GridIndex
ForestIndex::ForestIndex(GridIndex index) : index(index), dronesCount(0) {}

// Destructor
ForestIndex::~ForestIndex() = default;

// Copy Constructor
ForestIndex::ForestIndex(const ForestIndex& other) : index(other.index), dronesCount(other.dronesCount) {}

// Move Constructor
ForestIndex::ForestIndex(ForestIndex&& other) noexcept : index(other.index), dronesCount(other.dronesCount)
{
    other.dronesCount = 0;
}

// Copy Assignment
ForestIndex& ForestIndex::operator=(const ForestIndex& other)
{
    if (this != &other)
    {
        index = other.index;
        dronesCount = other.dronesCount;
    }
    return *this;
}

// Move Assignment
ForestIndex& ForestIndex::operator=(ForestIndex&& other) noexcept
{
    if (this != &other)
    {
        index = other.index;
        dronesCount = other.dronesCount;
        other.dronesCount = 0;
    }
    return *this;
}

// Comparison Operators
bool ForestIndex::operator==(const ForestIndex& other) const
{
    return index == other.index && dronesCount == other.dronesCount;
}

bool ForestIndex::operator!=(const ForestIndex& other) const
{
    return !(*this == other);
}

// Getters and Setters
GridIndex ForestIndex::get_index() const { return index; }
void ForestIndex::set_index(const GridIndex index) { this->index = index; }

int ForestIndex::get_x() const { return index.x; }
void ForestIndex::set_x(const int x) { index.x = x; }

int ForestIndex::get_y() const { return index.y; }
void ForestIndex::set_y(const int y) { index.y = y; }

unsigned int ForestIndex::get_dronesCount() const { return dronesCount; }
void ForestIndex::set_dronesCount(const unsigned int dronesCount) { this->dronesCount = dronesCount; }

// Increment and Decrement Operators
void ForestIndex::operator++() { ++dronesCount; }    // Prefix increment
void ForestIndex::operator++(int) { dronesCount++; } // Postfix increment
void ForestIndex::operator--() { if (dronesCount > 0) --dronesCount; }    // Prefix decrement
void ForestIndex::operator--(int) { if (dronesCount > 0) dronesCount--; } // Postfix decrement
