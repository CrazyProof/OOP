#pragma once
#include "Node.h"
#include <utility> // For std::swap

class Array
{
private:
    Node *data;
    int size;

public:
    // Constructor
    explicit Array(int len);

    // Destructor
    ~Array();

    // Copy Constructor
    Array(const Array &other);

    // Move Constructor
    Array(Array &&other) noexcept;

    // Copy Assignment Operator
    Array &operator=(const Array &other);

    // Move Assignment Operator
    Array &operator=(Array &&other) noexcept;

    // Subscript Operator (non-const)
    Node &operator[](int index);

    // Subscript Operator (const) - Good practice, though not strictly needed by main.cpp
    const Node &operator[](int index) const;

    // Getter for size (optional)
    int getSize() const;
};
