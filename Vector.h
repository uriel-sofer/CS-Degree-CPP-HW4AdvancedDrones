#ifndef VECTOR_H
#define VECTOR_H

/**
 * I wanted a dynamic array, and wanted to use templates, so i went ahead and implemented this class
 * Not strictly necessary but fun
 * @tparam T printable object
 */
template <typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize();

public:
    Vector();
    Vector(const Vector& other);
    Vector(Vector&& other);
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);
    ~Vector();

    void push_back(const T& value);
    void pop_back();

    T& operator[](size_t index); // Assumes correct input, due to inability to handle wrong input (yet)
    const T& operator[](size_t index) const; // Assumes correct input, due to inability to handle wrong input (yet)
    size_t getSize() const;
    size_t getCapacity() const;

    void clear(); // Clears the vector

    void print() const; // Prints all items in the vector (assumes printable)
};
// Implementations below

template <typename T>
Vector<T>::Vector() : data(nullptr), capacity(0), size(0)
{}

template <typename T>
Vector<T>::Vector(const Vector& other) : size(other.size), capacity(other.capacity)
{
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector&& other) : data(other.data), capacity(other.capacity), size(other.size)
{
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}


template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if (this != &other) {
        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other)
{
    if (this != &other)
    {
        delete[] data;

        data = other.data;
        size = other.size;
        capacity = other.capacity;

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}



template <typename T>
Vector<T>::~Vector()
{
    delete[] data;
}

template <typename T>
void Vector<T>::resize()
{
    const int newCapacity = capacity == 0 ? 2 : capacity * 2;
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size; ++i)
    {
        newData[i] = std::move(data[i]);
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
void Vector<T>::print() const
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << data[i] << std::endl;
    }
    std::cout << std::endl;
}

template <typename T>
void Vector<T>::push_back(const T& value)
{
    if (size == capacity)
    {
        resize();
    }
    data[size++] = value;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (size == 0)
    {
        return;
    }
    --size;
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
    return data[index];
}

template <typename T>
size_t Vector<T>::getSize() const
{
    return size;
}

template <typename T>
size_t Vector<T>::getCapacity() const
{
    return capacity;
}

template <typename T>
void Vector<T>::clear()
{
    size = 0;
    capacity = 0;
    resize();
}



#endif //VECTOR_H
