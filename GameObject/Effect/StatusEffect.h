#pragma once
#include <iostream>
#include "../Damage/Damage.h"

using namespace std;

class Player; 

enum class TickTrigger {
    none,
    endOfTurn,
    afterReceiveDamage,
    beforeReceiveDamage,
    endOfTurnOpponent
};

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
    TickTrigger _tickTrigger; // thời điểm giảm duration

public:
    explicit StatusEffect(int turns, TickTrigger tickAt)
        : _duration(turns), _tickTrigger(tickAt) {}

    virtual ~StatusEffect() = default;

public :
    TickTrigger getTickTrigger() const {
        return _tickTrigger;
    }

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
