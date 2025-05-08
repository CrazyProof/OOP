#pragma once
#include "dragon.h"
#include "weapon.h"

class Ninja
{
protected:
    Dragon dragon;
    Weapon weapon;

public:
    Ninja(string dragon_name, string weapon_name);
    virtual void describe();
};
