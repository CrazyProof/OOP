#include "ninja.h"
#include <iostream>
using namespace std;

Ninja::Ninja(string dragon_name, string weapon_name)
    : dragon(dragon_name), weapon(weapon_name) {}

void Ninja::describe()
{
    cout << "Ninja is coming!" << endl;
    cout << "Ninja is with " << dragon.get_name() << " and " << weapon.get_name() << "." << endl;
}
