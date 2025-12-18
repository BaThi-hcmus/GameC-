#pragma once 
#include "StatusEffect.h"
#include "../Player.h"

class StunEffect : public StatusEffect {
public:
    StunEffect(int turns) : StatusEffect(turns) {}

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::Stun;
    }
};
