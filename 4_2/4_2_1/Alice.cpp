#include "Alice.h"
#include "Part.h"

Alice::Alice(int partnum):partnum(partnum){
    partpoint = new Part[partnum];
    currentpart = 0;
}

Alice::~Alice(){
    delete[] partpoint;
}

void Alice::add_part(Part a){
    partpoint[currentpart] = a;
    currentpart++;
}

bool Alice::is_full(){
    if(currentpart == partnum){
        return true;
    }
    return false;
}

int Alice::run(){
    int sum = 0;
    for(int i = 0; i < partnum; i++){
        sum += partpoint[i].getid();
    }
    return sum;
}

std::ostream &operator<<(std::ostream &os, const Alice &A){
    os << "Build robot Alice";
    return os;
};