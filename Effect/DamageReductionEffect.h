#pragma once 
#include "StatusEffect.h"

class DamageReductionEffect : public StatusEffect {
private:
    float _ratio;

public:
    DamageReductionEffect(int turns, float r)
        : StatusEffect(turns), _ratio(r) {}

    void onApply(Player&, Damage* damage = nullptr) override {
        if(damage) {
            int reduced = static_cast<int>((damage->getAmount()) * _ratio);
            damage->setAmount(damage->getAmount() - reduced);
            cout << "[REDUCE] Doi thu giam " << _ratio * 100 << "% sat thuong\n";
        }
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::DamageReduction;
    }
};
