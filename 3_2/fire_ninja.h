#pragma once
#include "ninja.h"

class FireNinja : public Ninja
{
public:
    FireNinja(string dragon_name, string weapon_name);
    void describe() override;
    void fire_power();
};
