#pragma once 
#include "StatusEffect.h"

class CriticalStrikeEffect : public StatusEffect {
private:
    float _chance;
    float _multiplier;

public:
    CriticalStrikeEffect(int turns, float c, float m)
        : StatusEffect(turns), _chance(c), _multiplier(m) {}

    void onApply(Player&, Damage* damage = nullptr) override {
        if(damage) {
            if (rand() % 100 < _chance * 100) {
                damage->setAmount(static_cast<int>((damage->getAmount()) * _multiplier));
                cout << "[CRIT] Sat thuong chi mang("<<_chance*100<<" %)"<< ".Ban duoc x" << _multiplier <<" damage\n";
            }
        }
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::CriticalStrike;
    }
};
