#pragma once 
#include "StatusEffect.h"

class DamageReductionEffect : public StatusEffect {
    float ratio;

public:
    DamageReductionEffect(int turns, float r)
        : StatusEffect(turns), ratio(r) {}

    void onApply(Player&, Damage* damage = nullptr) override {
        if(damage) {
            int reduced = static_cast<int>((damage->amount) * ratio);
            damage->amount -= reduced;
            std::cout << "[REDUCE] Doi thu giam " << ratio * 100 << "% sat thuong\n";
        }
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::DamageReduction;
    }
};
