#include "Alice.h"
#include "Part.h"

Alice::Alice(int partnum) : Robot(partnum) {}

Alice::~Alice() {}

void Alice::add_part(Part a)
{
    partpoint[currentpart++] = a;
}

bool Alice::is_full()
{
    return currentpart == partnum;
}

int Alice::run()
{
    int sum = 0;
    for (int i = 0; i < partnum; i++)
    {
        sum += partpoint[i].getid();
    }
    return sum;
}

std::ostream &Alice::print(std::ostream &os) const
{
    os << "Build robot Alice";
    return os;
}