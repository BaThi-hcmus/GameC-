#pragma once 
#include "Damage.h"
#include "../Player.h"

class PiercingDamage : public Damage {
public:
    void apply(Player& target) override {
        target.hp -= amount; // bỏ qua shield
    }
};