// JackpotEffect.h
#pragma once
#include "StatusEffect.h"

class JackpotEffect : public StatusEffect {
public:
    JackpotEffect(int turns) : StatusEffect(turns) {}

    void onTurnStart(Player& p) override;
};
