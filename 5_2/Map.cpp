#include "Map.h"
#include <string>

Map::Map(int n): sz(0), capacity(n){
    data = new Pair[n];
}

Map::~Map(){
    delete[] data;
}

int Map::operator[](const std::string& key) const{
    for(int i = 0; i < sz; i++){
        if(data[i].hasKey(key)){
            return data[i].getVal();
        }
    }
    return 0;
}

int &Map::operator[](const std::string &key){
    for (int i = 0; i < sz; i++)
    {
        if (data[i].hasKey(key))
        {
            return data[i].getVal();
        }
    }
    if (sz < capacity)
    {
        data[sz].reset(key, 0);
        return data[sz++].getVal();
    }
}

int Map::size() const{
    return sz;
}