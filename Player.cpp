#include "Player.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "Effect/JackpotEffect.h"
#include "Effect/StunEffect.h"
#include "ConfigKey.h"
#include "ConfigKeyMap.h"

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

// ================= EFFECT SYSTEM =================
void Player::addEffect(unique_ptr<StatusEffect> eff) {
    effects.push_back(move(eff));
}

// ============ QUERY EFFECT =============
bool Player::hasEffect(EffectTag tag) {
    for (auto& it : effects)
        if (it->hasTag(tag))
            return true;
    return false;
}

// những hiệu ứng nào hết vòng đời => bị loại bỏ
void Player::updateEffectsEndTurn() {
    for (auto it = effects.begin(); it != effects.end();) {
        (*it)->onTurnEnd(*this); //dành cho các effect có tác dụng cuối lượt : ví dụ như : thiêu đốt

        if ((*it)->tick()) {    //nếu hiệu ứng đã hết vòng đời => xóa
            (*it)->onRemove(*this);
            it = effects.erase(it);
        } else {
            ++it;
        }
    }
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

// ================= RECEIVE ATTACK =================
void Player::receiveAttack(int baseDamage, Player& attacker) {
    cout << "\n[ATTACK] Base damage: " << baseDamage << "\n";

    float atkScale = GameConfig::instance().getFloat(ConfigKey::ATTACK_ENERGY_DAMAGE_SCALE);
    int damage = static_cast<int>(
        baseDamage * (1.0f + attacker.attackEnergy * atkScale)
    );

    // attacker effects (crit, buff...)
    for (auto& eff : attacker.effects) {
        eff->onBeforeDealDamage(attacker, damage);
    }

    float defScale = GameConfig::instance().getFloat(ConfigKey::DEFENSE_ENERGY_DAMAGE_REDUCTION_SCALE);
    damage -= static_cast<int>(defenseEnergy * defScale * baseDamage);
    damage = max(0, damage);

    // defender BEFORE receive (dodge, ...)
    for (auto& eff : effects) {
        eff->onBeforeReceiveDamage(*this, damage);
    }

    if (damage == 0) {
        cout << ">> Ne don!\n";
        return;
    }

    // defender AFTER receive (reduction)
    for (auto& eff : effects) {
        eff->onAfterReceiveDamage(*this, damage);
    }

    int absorbed = min(shield, damage);
    shield -= absorbed;
    damage -= absorbed;

    hp -= damage;
    hp = max(0, hp);

    cout << ">> Damage cuoi: " << damage << " | HP: " << hp << "\n";
}

// ================= PIERCE ATTACK =================
void Player::receivePierceAttack(int baseDamage, Player& attacker) {
    cout << "[PIERCE] " << baseDamage << "\n";

    float atkScale = GameConfig::instance().getFloat(ConfigKey::ATTACK_ENERGY_DAMAGE_SCALE);
    int damage = static_cast<int>(
        baseDamage * (1.0f + attacker.attackEnergy * atkScale)
    );

    float defScale = GameConfig::instance().getFloat(ConfigKey::DEFENSE_ENERGY_DAMAGE_REDUCTION_SCALE);
    damage -= static_cast<int>(defenseEnergy * defScale * baseDamage);
    damage = max(0, damage);

    hp -= damage;
    hp = max(0, hp);

    cout << ">> HP mat: " << damage << " | HP: " << hp << "\n";
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

// ================= JACKPOT =================
void Player::rollJackpot(int times, Player& target) {
    if (this->hasEffect(EffectTag::Jackpot)) {
        cout << "Jackpot dang bi khoa!\n";
        return;
    }

    for (int i = 0; i < times; i++) {
        int baseChance = GameConfig::instance().getInt(ConfigKey::JACKPOT_CHANCE);
        int chance = baseChance + rage * 2;
        int roll = rand() % 100;

        cout << "Quay Jackpot (" << chance << "%)... ";

        if (roll < chance) {
            cout << "TRUNG!!!\n";
            rage = 0;
            this->activateJackpot(target);
            return;
        }
        cout << "That bai\n";
    }
}

void Player::activateJackpot(Player& target) {
    //số lượt buff hiệu ứng jackpot
    int buffTurns = GameConfig::instance().getInt(ConfigKey::JACKPOT_DURATION_TURNS);

    auto eff = std::make_unique<JackpotEffect>(buffTurns);
    eff->onApply(*this);
    this->addEffect(move(eff));

    //gây choáng đối thủ trong 1 lượt
    target.addEffect(std::make_unique<StunEffect>(1));

    std::cout << "[JACKPOT] Kich hoat!\n";
}

