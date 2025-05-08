#pragma once
#include "Part.h"
#include <iostream>

class Robot
{
protected:
    int partnum;
    Part *partpoint;
    int currentpart;

public:
    Robot(int partnum);
    virtual ~Robot();
    virtual void add_part(Part) = 0;
    virtual bool is_full() = 0;
    virtual int run() = 0;
    virtual std::ostream &print(std::ostream &os) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Robot &robot)
    {
        return robot.print(os);
    }
};
