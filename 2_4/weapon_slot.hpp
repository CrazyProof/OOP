// weapon_slot.hpp
#pragma once
#include "weapon.hpp"
#include <memory>
#include <algorithm>

class WeaponSlot
{
private:
    std::unique_ptr<Weapon> weapon;

public:
    WeaponSlot() = default;

    // Move assignment
    WeaponSlot &operator=(WeaponSlot &&other) noexcept
    {
        if (this != &other)
        {
            weapon = std::move(other.weapon);
        }
        return *this;
    }

    // Copy assignment for op=3
    WeaponSlot &operator=(const WeaponSlot &other)
    {
        if (this != &other)
        {
            if (other.weapon)
            {
                weapon = std::make_unique<Weapon>(other.weapon->penetration);
                for (int a : other.weapon->spells)
                {
                    if (a % 2 == 0)
                    {
                        weapon->spells.push_back(a);
                    }
                }
            }
            else
            {
                weapon.reset();
            }
        }
        return *this;
    }

    void create_weapon(int p)
    {
        weapon = std::make_unique<Weapon>(p);
    }

    void add_spell(int a)
    {
        weapon->spells.push_back(a);
    }

    int calc_damage_typeA(int d) const
    {
        int total = 0;
        int p = weapon->penetration;
        for (int a : weapon->spells)
        {
            int effective_d = std::max(d - p, 0);
            int damage = a - effective_d;
            if (damage > 0)
            {
                total += damage;
            }
        }
        return total;
    }

    int calc_damage_typeB() const
    {
        int total = 0;
        int p = weapon->penetration;
        int current_defense = 0;
        for (int a : weapon->spells)
        {
            int effective_d = std::max(current_defense - p, 0);
            int damage = a - effective_d;
            if (damage > 0)
            {
                total += damage;
            }
            current_defense++;
        }
        return total;
    }

    int calc_damage_typeC() const
    {
        int total = 0;
        int p = weapon->penetration;
        int current_defense = 0;
        for (int a : weapon->spells)
        {
            int effective_d = std::max(current_defense - p, 0);
            int damage_original = a - effective_d;
            if (damage_original <= 0)
            {
                continue;
            }
            if (damage_original % 2 == 1)
            {
                total += damage_original;
                current_defense++;
            }
            else
            {
                total += damage_original / 2;
            }
        }
        return total;
    }
};