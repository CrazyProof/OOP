#include "ice_ninja.h"
#include <iostream>
using namespace std;

IceNinja::IceNinja(string dragon_name, string weapon_name)
    : Ninja(dragon_name, weapon_name) {}

void IceNinja::describe()
{
    cout << "Ice ninja is coming!" << endl;
    cout << "Ice ninja is with " << dragon.get_name() << " and " << weapon.get_name() << "." << endl;
}

void IceNinja::ice_power()
{
    cout << "You will be the dust of frozen bones!" << endl;
}
