#pragma once 
#include "StatusEffect.h"

class CriticalStrikeEffect : public StatusEffect {
    float chance;
    float multiplier;

public:
    CriticalStrikeEffect(int turns, float c, float m)
        : StatusEffect(turns), chance(c), multiplier(m) {}

    void onBeforeDealDamage(Player&, int& damage) override {
        if (rand() % 100 < chance * 100) {
            damage = static_cast<int>(damage * multiplier);
            std::cout << "[CRIT] Chi mang! Sat thuong tang!\n";
        }
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::CriticalStrike;
    }
};
