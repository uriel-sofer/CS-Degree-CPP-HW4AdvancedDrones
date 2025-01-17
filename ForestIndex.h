#ifndef FORESTINDEX_H
#define FORESTINDEX_H

/**
 * Represents a coordinate tuple.
 */
struct GridIndex
{
    int x;
    int y;

    GridIndex(const int x = 0, const int y = 0) : x(x), y(y) {}

    bool operator==(const GridIndex& grid_index) const
    {
        return x == grid_index.x && y == grid_index.y;
    }

    bool operator!=(const GridIndex& grid_index) const
    {
        return !(*this == grid_index);
    }
};

/**
 * Used to count drones in each coordinate in the forest.
 */
class ForestIndex {
    GridIndex index;           // Grid coordinate
    unsigned int dronesCount;  // Count of drones in this grid cell

public:
    // Constructors and Destructor
    ForestIndex();
    ForestIndex(int x, int y);
    ForestIndex(GridIndex index);
    ~ForestIndex();
    ForestIndex(const ForestIndex& other);
    ForestIndex(ForestIndex&& other) noexcept;
    ForestIndex& operator=(const ForestIndex& other);
    ForestIndex& operator=(ForestIndex&& other) noexcept;

    // Comparison Operators
    bool operator==(const ForestIndex& other) const;
    bool operator!=(const ForestIndex& other) const;

    // Getters and Setters
    GridIndex get_index() const;
    void set_index(GridIndex index);
    int get_x() const;
    void set_x(int x);
    int get_y() const;
    void set_y(int y);
    unsigned int get_dronesCount() const;
    void set_dronesCount(unsigned int dronesCount);

    // Increment and Decrement Operators
    void operator++();    // Prefix increment
    void operator++(int); // Postfix increment
    void operator--();    // Prefix decrement
    void operator--(int); // Postfix decrement
};

#endif // FORESTINDEX_H
