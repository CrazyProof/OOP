#pragma once
#include <iostream>

class Part
{
    int id;

public:
    Part() = default;
    Part(int);
    ~Part();
    int getid();
};