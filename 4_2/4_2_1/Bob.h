#pragma once
#include <iostream>
#include "Part.h"

class Bob
{
    int partnum;
    Part *partpoint;
    int currentpart;

public:
    Bob() = default;
    Bob(int);
    ~Bob();
    void add_part(Part);
    bool is_full();
    int run();
    friend std::ostream &operator<<(std::ostream &, const Bob &);
};