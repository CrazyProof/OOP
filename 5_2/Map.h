#pragma once
#include "Pair.h"
#include <string>

class Map{
    Pair * data;
    int sz;
    int capacity;
public:
    Map(int n);
    // TODO
    ~Map();
    int& operator[](const std::string& s);
    int operator[](const std::string& s) const;
    int size() const;
};