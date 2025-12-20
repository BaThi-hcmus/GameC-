#pragma once 
#include "Damage.h"
#include "../Player/Player.h"

class PiercingDamage : public Damage {
public:
    void apply(Player& target) override {
        target.setHp(target.getHp() - _amount);
    }
};