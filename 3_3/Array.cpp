#include "Array.h"
#include <utility> // For std::swap and std::move

// Constructor: Allocates memory and initializes size.
// Calls Node's default constructor 'len' times.
Array::Array(int len) : data(new Node[len]), size(len) {}

// Destructor: Deallocates memory.
// Calls Node's destructor for each element.
Array::~Array()
{
    delete[] data;
}

// Copy Constructor: Performs a deep copy.
Array::Array(const Array &other) : size(other.size)
{
    data = new Node[size];
    for (int i = 0; i < size; ++i)
    {
        data[i] = other.data[i]; // Calls Node's copy assignment operator
    }
}

// Move Constructor: Transfers ownership. No Node constructions/assignments occur.
Array::Array(Array &&other) noexcept : data(other.data), size(other.size)
{
    // Prevent the moved-from object's destructor from deleting the data
    other.data = nullptr;
    other.size = 0;
}

// Copy Assignment Operator: Handles self-assignment and performs a deep copy.
Array &Array::operator=(const Array &other)
{
    if (this != &other)
    { // Protect against self-assignment
        // If sizes are different, reallocate. Otherwise, reuse existing memory.
        if (size != other.size)
        {
            delete[] data; // Free old memory
            size = other.size;
            data = new Node[size]; // Allocate new memory
        }
        // Copy elements
        for (int i = 0; i < size; ++i)
        {
            data[i] = other.data[i]; // Calls Node's copy assignment operator
        }
    }
    return *this;
}

// Move Assignment Operator: Transfers ownership.
Array &Array::operator=(Array &&other) noexcept
{
    if (this != &other)
    {                  // Protect against self-assignment
        delete[] data; // Free existing resource

        // Transfer ownership from other
        data = other.data;
        size = other.size;

        // Leave other in a valid state
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

// Subscript Operator (non-const): Returns a reference to the element.
Node &Array::operator[](int index)
{
    // Add bounds checking if necessary:
    // if (index < 0 || index >= size) { /* handle error */ }
    return data[index];
}

// Subscript Operator (const): Returns a const reference to the element.
const Node &Array::operator[](int index) const
{
    // Add bounds checking if necessary:
    // if (index < 0 || index >= size) { /* handle error */ }
    return data[index];
}

// Getter for size
int Array::getSize() const
{
    return size;
}
