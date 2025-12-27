#pragma once
#include <memory>
#include <vector>
#include "../NewGameConfig/GameConfig.h"
#include "../Effect/StatusEffect.h"
#include "../Effect/EffectScheduler.h"
#include "../Card/Card.h"

using namespace std;

class Player {
protected :
    // ===== CORE STATS =====
    int _hp;
    int _shield;
    int _rage;

    // ===== ENERGY =====
    int _attackEnergy;
    int _defenseEnergy;
    int _jackpotEnergy;

    bool _isJackpotNerfed; //BOT
public:
    int getHp();
    int getShield();
    int getRage();
    int getAttackEnergy();
    int getDefenseEnergy();
    int getJackpotEnergy();

    void setHp(int hp);
    void setShield(int shield);
    void setRage(int rage);
    void setAttackEnergy(int attackEnergy);
    void setDefenseEnergy(int defenseEnergy);
    void setJackpotEnergy(int jackpotEnergy);
public:
    Player();

public:
    // ===== STATIC CONFIG =====
    static int MAX_HP;
    static int MAX_RAGE;
    static int MAX_CURSED_ENERGY;

    static void loadConfig();

    // ===== TURN =====
    void resetTurnState();

    // ===== GAMEPLAY =====
    virtual void allocateCursedEnergy();
    virtual vector<Card*> pickCards(const vector<unique_ptr<Card>>& hand);

    void addShield(int amount);
    void increaseRage(int amount);

    void setJackpotNerf(bool val); //BOT
    bool isJackpotNerfed() const ; //BOT
    virtual bool isBot() const { return false; } //BOT
    virtual string getName() const { return "Nguoi Choi"; } //BOT
};
