#pragma once
#include "ninja.h"

class IceNinja : public Ninja
{
public:
    IceNinja(string dragon_name, string weapon_name);
    void describe() override;
    void ice_power();
};
