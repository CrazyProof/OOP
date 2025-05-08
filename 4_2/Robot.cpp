#include "Robot.h"

Robot::Robot(int partnum) : partnum(partnum), currentpart(0)
{
    partpoint = new Part[partnum];
}

Robot::~Robot()
{
    delete[] partpoint;
}
