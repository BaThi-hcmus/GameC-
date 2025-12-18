#pragma once 
#include "StatusEffect.h"

class DodgeEffect : public StatusEffect {
    float chance;

public:
    DodgeEffect(int turns, float c)
        : StatusEffect(turns), chance(c) {}

    void onBeforeReceiveDamage(Player&, int& damage) override {
        if (rand() % 100 < chance * 100) {
            std::cout << "[DODGE] Ne don thanh cong!\n";
            damage = 0;
        }
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::Dodge;
    }
};
