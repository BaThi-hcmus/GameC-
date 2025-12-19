#pragma once 
#include "StatusEffect.h"

class CriticalStrikeEffect : public StatusEffect {
    float chance;
    float multiplier;

public:
    CriticalStrikeEffect(int turns, float c, float m)
        : StatusEffect(turns), chance(c), multiplier(m) {}

    void onApply(Player&, Damage* damage = nullptr) override {
        if(damage) {
            if (rand() % 100 < chance * 100) {
                damage->amount = static_cast<int>((damage->amount) * multiplier);
                std::cout << "[CRIT] Sat thuong chi mang("<<chance*100<<" %)"<< ".Ban duoc x" << multiplier <<" damage\n";
            }
        }
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::CriticalStrike;
    }
};
