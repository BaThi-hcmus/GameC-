// DamageReductionEffect.h
#pragma once
#include "StatusEffect.h"

class DamageReductionEffect : public StatusEffect {
    float ratio;

public:
    DamageReductionEffect(int turns, float r)
        : StatusEffect(turns), ratio(r) {}

    void onAfterReceiveDamage(Player&, int& damage) override;
};
