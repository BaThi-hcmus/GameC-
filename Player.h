#pragma once
#include <memory>
#include <vector>
#include "GameConfig.h"
#include "Effect/StatusEffect.h"

using namespace std;

class Player {
public:
    // ===== STATIC CONFIG =====
    static int MAX_HP;
    static int MAX_RAGE;
    static int MAX_CURSED_ENERGY;

    // ===== CORE STATS =====
    int hp;
    int shield;
    int rage;

    // ===== ENERGY =====
    int attackEnergy;
    int defenseEnergy;
    int jackpotEnergy;

    // ===== EFFECT SYSTEM =====
    std::vector<std::unique_ptr<StatusEffect>> effects;

    // ===== QUERY EFFECT =====
    bool hasEffect(EffectTag tag);

    // ===== LIFECYCLE =====
    Player();
    static void loadConfig();

    // ===== EFFECT MANAGEMENT =====
    void addEffect(std::unique_ptr<StatusEffect> eff);
    void updateEffectsEndTurn();

    // ===== TURN =====
    void resetTurnState();
    void updateStatus();

    // ===== GAMEPLAY =====
    void allocateCursedEnergy(int atk, int def, int jackpot);
    void receiveAttack(int baseDamage, Player& attacker);
    void receivePierceAttack(int baseDamage, Player& attacker);

    void addShield(int amount);
    void increaseRage(int amount);

    // ===== JACKPOT =====
    void rollJackpot(int times, Player& target);
    void activateJackpot(Player& target);
};
