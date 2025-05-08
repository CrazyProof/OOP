#include "fire_ninja.h"
#include <iostream>
using namespace std;

FireNinja::FireNinja(string dragon_name, string weapon_name)
    : Ninja(dragon_name, weapon_name) {}

void FireNinja::describe()
{
    cout << "Fire ninja is coming!" << endl;
    cout << "Fire ninja is with " << dragon.get_name() << " and " << weapon.get_name() << "." << endl;
}

void FireNinja::fire_power()
{
    cout << "I will burn the night!" << endl;
}
