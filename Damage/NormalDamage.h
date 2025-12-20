#pragma once
#include "Damage.h"
#include "../Player/Player.h"

class NormalDamage : public Damage {
public:
    void apply(Player& target) override {
        int dmgLeft = _amount;
        if (target.getShield() > 0) {
            int absorbed = min(dmgLeft, target.getShield());
            target.setShield(target.getShield() - absorbed);
            dmgLeft -= absorbed;
        }
        target.setHp(target.getHp() - dmgLeft);
    }
};


