#pragma once
#include <iostream>

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
    int duration;
public:
    explicit StatusEffect(int turns) : duration(turns) {}
    virtual ~StatusEffect() = default;

    // ===== QUERY =====
    virtual bool hasTag(EffectTag) { return false; }

    // ===== LIFECYCLE =====
    virtual void onApply(Player&) {}
    virtual void onRemove(Player&) {}

    // ===== TURN =====
    virtual void onTurnStart(Player&) {}
    virtual void onTurnEnd(Player&) {}

    // ===== COMBAT =====
    virtual void onBeforeDealDamage(Player&, int&) {}
    virtual void onBeforeReceiveDamage(Player&, int&) {}
    virtual void onAfterReceiveDamage(Player&, int&) {}

    bool tick() {
        return --duration <= 0;
    }
};
