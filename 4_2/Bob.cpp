#include "Bob.h"
#include "Part.h"

Bob::Bob(int partnum) : Robot(partnum) {}

Bob::~Bob() {}

void Bob::add_part(Part a)
{
    partpoint[currentpart++] = a;
}

bool Bob::is_full()
{
    return currentpart == partnum;
}

int Bob::run()
{
    int sum = 0;
    for (int i = 0; i < partnum; i++)
    {
        sum += partpoint[i].getid() * partpoint[i].getid();
    }
    return sum;
}

std::ostream &Bob::print(std::ostream &os) const
{
    os << "Build robot Bob";
    return os;
}