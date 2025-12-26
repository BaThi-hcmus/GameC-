#include "Player.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <format>
#include "../Effect/JackpotEffect.h"
#include "../Effect/StunEffect.h"
#include "../NewGameConfig/ConfigKey.h"
#include "../NewGameConfig/ConfigKeyMap.h"
#include "../Effect/EffectScheduler.h"
#include "../Effect/ScheduledEffect.h"

using namespace std;

// ================= STATIC =================
int Player::MAX_HP = 0;
int Player::MAX_RAGE = 0;
int Player::MAX_CURSED_ENERGY = 0;

// ================= CONSTRUCTOR =================
Player::Player()
    : _hp(MAX_HP),
      _shield(0),
      _rage(0),
      _attackEnergy(0),
      _defenseEnergy(0),
      _jackpotEnergy(0) {}

int Player::getHp() {
    return _hp;
}

int Player::getShield() {
    return _shield;
}

int Player::getRage() {
    return _rage;
}

int Player::getAttackEnergy() {
    return _attackEnergy;
}

int Player::getDefenseEnergy() {
    return _defenseEnergy;
}

int Player::getJackpotEnergy() {
    return _jackpotEnergy;
}

void Player::setHp(int hp) {
    _hp = hp;
}

void Player::setShield(int shield) {
    _shield = shield;
}

void Player::setRage(int rage) {
    _rage = rage;
}

void Player::setAttackEnergy(int attackEnergy) {
    _attackEnergy = attackEnergy;
}

void Player::setDefenseEnergy(int defenseEnergy) {
    _defenseEnergy = defenseEnergy;
}

void Player::setJackpotEnergy(int jackpotEnergy) {
    _jackpotEnergy = jackpotEnergy;
}

void Player::setJackpotNerf(bool val) {
    _isJackpotNerfed = val;
}

bool Player::isJackpotNerfed() const {
    return _isJackpotNerfed;
}

// ================= CONFIG =================
void Player::loadConfig() {
    auto& conf = GameConfig::instance();
    MAX_HP = conf.getInt(ConfigKey::PLAYER_MAX_HP);
    MAX_RAGE = conf.getInt(ConfigKey::PLAYER_MAX_RAGE);
    MAX_CURSED_ENERGY = conf.getInt(ConfigKey::PLAYER_CURSED_ENERGY_PER_TURN);
}

// ================= TURN =================
void Player::resetTurnState() {
    _attackEnergy = 0;
    _defenseEnergy = 0;
    _jackpotEnergy = 0;
}

// ================= ENERGY =================
void Player::allocateCursedEnergy(int atk, int def, int jackpot) {
    if (atk + def + jackpot != MAX_CURSED_ENERGY) {
        cout << "Tong chu luc khong hop le!\n";
        return;
    }

    _attackEnergy = atk;
    _defenseEnergy = def;
    _jackpotEnergy = jackpot;
    // mỗi điểm phân bố cho jackpot sẽ cộng thêm vào cho thanh nộ II
    if (jackpot > 0)
        this->increaseRage(jackpot);
}

// ================= SHIELD =================
void Player::addShield(int amount) {
    _shield += amount;
    cout << "[SHIELD] +" << amount << " | Tong: " << _shield << "\n";
}

// ================= RAGE =================
void Player::increaseRage(int amount) {
    _rage = min(MAX_RAGE, _rage + amount);
    cout << "[RAGE] +" << amount << " | Tong: " << _rage << "\n";
}


