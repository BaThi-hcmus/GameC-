#pragma once 
#include "StatusEffect.h"

class DamageReductionEffect : public StatusEffect {
private:
    float _ratio;

public:
    DamageReductionEffect(int turns, float r, TickTrigger trigger)
        : StatusEffect(turns, trigger), _ratio(r) {}

    void onApply(Player&, Damage* damage = nullptr) override {
        if(damage) {
            int reduced = static_cast<int>((damage->getAmount()) * _ratio);
            damage->setAmount(damage->getAmount() - reduced);
            cout << "[CARD REDUCE DAMAGE] Doi thu giam " << _ratio * 100 << "% sat thuong\n";
        }
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::DamageReduction;
    }
};
