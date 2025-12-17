// StunEffect.h
#pragma once
#include "StatusEffect.h"
#include <iostream>

class StunEffect : public StatusEffect {
public:
    StunEffect(int turns) : StatusEffect(turns) {}

    void onApply(Player& p) override;
    void onRemove(Player& p) override;
};
