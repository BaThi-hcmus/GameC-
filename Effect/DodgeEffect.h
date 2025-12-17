// DodgeEffect.h
#pragma once
#include "StatusEffect.h"

class DodgeEffect : public StatusEffect {
    float chance;

public:
    DodgeEffect(int turns, float c)
        : StatusEffect(turns), chance(c) {}

    void onApply(Player& p) override;
    void onRemove(Player& p) override;
};
