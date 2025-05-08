#pragma once
#include<iostream>
#include"Part.h"

class Alice
{
    int partnum;
    Part* partpoint;
    int currentpart;

public:
    Alice() = default;
    Alice(int);
    ~Alice();
    void add_part(Part);
    bool is_full();
    int run();
    friend std::ostream& operator << (std::ostream&, const Alice&);
};