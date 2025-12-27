#pragma once 
#include "StatusEffect.h"
#include "../Player/Player.h"

class StunEffect : public StatusEffect {
public:
    StunEffect(int turns, TickTrigger trigger) : StatusEffect(turns, trigger) {}

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::Stun;
    }
};
