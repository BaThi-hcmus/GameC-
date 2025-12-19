#pragma once
#include <memory>
#include <vector>
#include "GameConfig.h"
#include "Effect/StatusEffect.h"
#include "Effect/EffectScheduler.h"
#include "StateNewGame.h"

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

    // ===== LIFECYCLE =====
    Player();
    static void loadConfig();

    // ===== TURN =====
    void resetTurnState();

    // ===== GAMEPLAY =====
    void allocateCursedEnergy(int atk, int def, int jackpot);

    void addShield(int amount);
    void increaseRage(int amount);
};
