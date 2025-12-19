#pragma once
#include "Damage.h"
#include "../Player.h"

class NormalDamage : public Damage {
public:
    void apply(Player& target) override {
        int dmgLeft = amount;
        if (target.shield > 0) {
            int absorbed = std::min(dmgLeft, target.shield);
            target.shield -= absorbed;
            dmgLeft -= absorbed;
        }
        target.hp -= dmgLeft;
    }
};


