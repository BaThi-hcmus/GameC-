#pragma once
#include <iostream>
#include "../Damage/Damage.h"

using namespace std;

class Player; 

enum class EffectTag {
    Jackpot,
    Stun,
    Dodge,
    DamageReduction,
    CriticalStrike
};

class StatusEffect {
protected:
    int _duration;
public:
    explicit StatusEffect(int turns) : _duration(turns) {}
    virtual ~StatusEffect() = default;

    // ===== QUERY =====
    virtual bool hasTag(EffectTag) { return false; }

    // ===== LIFECYCLE =====
    virtual void onApply(Player&, Damage* dmg = nullptr) {}

    virtual void tick() {
        _duration--;
    }

    bool isExpired() const {
        return _duration <= 0;
    }
};
