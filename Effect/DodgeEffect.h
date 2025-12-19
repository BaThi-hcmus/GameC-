#pragma once 
#include "StatusEffect.h"

class DodgeEffect : public StatusEffect {
    float chance;

public:
    DodgeEffect(int turns, float c)
        : StatusEffect(turns), chance(c) {}

    void onApply(Player&, Damage* damage = nullptr) override {
        if(damage) {
            if (rand() % 100 < chance * 100) {
                std::cout << "[DODGE] Doi thu ne don thanh cong!\n";         
                damage->amount = 0;
            }
        }
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::Dodge;
    }
};
