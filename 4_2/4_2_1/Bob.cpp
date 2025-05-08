#include "Bob.h"
#include "Part.h"

Bob::Bob(int partnum): partnum(partnum)
{
    partpoint = new Part[partnum];
    currentpart = 0;
}

Bob::~Bob()
{
    delete[] partpoint;
}

void Bob::add_part(Part a)
{
    partpoint[currentpart] = a;
    currentpart++;
}

bool Bob::is_full()
{
    if (currentpart == partnum)
    {
        return true;
    }
    return false;
}

int Bob::run()
{
    int sum = 0;
    for (int i = 0; i < partnum; i++)
    {
        sum += (partpoint[i].getid()*partpoint[i].getid());
    }
    return sum;
}
std::ostream &operator<<(std::ostream &os, const Bob &B){
    os << "Build robot Bob";
    return os;
}