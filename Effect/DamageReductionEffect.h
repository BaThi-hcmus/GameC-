#pragma once 
#include "StatusEffect.h"

class DamageReductionEffect : public StatusEffect {
    float ratio;

public:
    DamageReductionEffect(int turns, float r)
        : StatusEffect(turns), ratio(r) {}

    void onAfterReceiveDamage(Player&, int& damage) override {
        int reduced = static_cast<int>(damage * ratio);
        damage -= reduced;
        std::cout << "[REDUCE] Giam " << ratio * 100 << "% sat thuong\n";
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::DamageReduction;
    }
};
