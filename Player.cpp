#include "Player.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "Effect/JackpotEffect.h"
#include "Effect/StunEffect.h"
#include "ConfigKey.h"
#include "ConfigKeyMap.h"
#include "Effect/EffectScheduler.h"
#include "Effect/ScheduledEffect.h"
#include <format>

using namespace std;

// ================= STATIC =================
int Player::MAX_HP = 0;
int Player::MAX_RAGE = 0;
int Player::MAX_CURSED_ENERGY = 0;

// ================= CONSTRUCTOR =================
Player::Player()
    : hp(MAX_HP),
      shield(0),
      rage(0),
      attackEnergy(0),
      defenseEnergy(0),
      jackpotEnergy(0) {}

// ================= CONFIG =================
void Player::loadConfig() {
    auto& conf = GameConfig::instance();
    MAX_HP = conf.getInt(ConfigKey::PLAYER_MAX_HP);
    MAX_RAGE = conf.getInt(ConfigKey::PLAYER_MAX_RAGE);
    MAX_CURSED_ENERGY = conf.getInt(ConfigKey::PLAYER_CURSED_ENERGY_PER_TURN);
}

// ================= TURN =================
void Player::resetTurnState() {
    attackEnergy = 0;
    defenseEnergy = 0;
    jackpotEnergy = 0;
}

// ================= ENERGY =================
void Player::allocateCursedEnergy(int atk, int def, int jackpot) {
    if (atk + def + jackpot != MAX_CURSED_ENERGY) {
        cout << "Tong chu luc khong hop le!\n";
        return;
    }

    attackEnergy = atk;
    defenseEnergy = def;
    jackpotEnergy = jackpot;
    // mỗi điểm phân bố cho jackpot sẽ cộng thêm vào cho thanh nộ II
    if (jackpot > 0)
        this->increaseRage(jackpot);
}

// ================= SHIELD =================
void Player::addShield(int amount) {
    shield += amount;
    cout << "[SHIELD] +" << amount << " | Tong: " << shield << "\n";
}

// ================= RAGE =================
void Player::increaseRage(int amount) {
    rage = min(MAX_RAGE, rage + amount);
    cout << "[RAGE] +" << amount << " | Tong: " << rage << "\n";
}


