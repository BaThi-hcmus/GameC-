#pragma once 
#include "StatusEffect.h"

class DodgeEffect : public StatusEffect {
private:
    float _chance;

public:
    DodgeEffect(int turns, float c, TickTrigger trigger)
        : StatusEffect(turns, trigger), _chance(c) {}

    void onApply(Player&, Damage* damage = nullptr) override {
        if(damage) {
            if (rand() % 100 < _chance * 100) {
                cout << "[CARD DODGE] Doi thu ne don thanh cong!\n";         
                damage->setAmount(0);
            }
        }
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::Dodge;
    }
};
