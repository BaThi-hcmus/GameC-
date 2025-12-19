#pragma once
#include "Card.h"
#include "GameConfig.h"

class StateNewGame;

// =============== NHÓM GÂY SÁT THƯƠNG ===================

class DamageCard : public Card {
private:
    int damageAmount;
public:
    DamageCard(int dmg = GameConfig::instance().getInt(ConfigKey::CARD_DAMAGE_NORMAL));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};

class StunAttackCard : public Card {
private:
    int damageAmount;
public:
    StunAttackCard(int dmg = GameConfig::instance().getInt(ConfigKey::CARD_DAMAGE_STUN));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};

class PierceAttackCard : public Card {
private:
    int damageAmount;
public:
    PierceAttackCard(int dmg = GameConfig::instance().getInt(ConfigKey::CARD_DAMAGE_PIERCE));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};

// ================= NHÓM PHÒNG THỦ ======================

class ShieldCard_50 : public Card {
private:
    int shieldAmount;
public:
    ShieldCard_50(int shield = GameConfig::instance().getInt(ConfigKey::CARD_SHIELD_GAIN));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};

class ReduceDamageCard : public Card {
private:
    float reductionRatio;
public:
    ReduceDamageCard(float ratio = GameConfig::instance().getFloat(ConfigKey::CARD_DAMAGE_REDUCTION_RATIO));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};

class DodgeCard : public Card {
private:
    float dodgeChance;
public:
    DodgeCard(float chance = GameConfig::instance().getFloat(ConfigKey::CARD_DODGE_CHANCE));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};

// ================== NHÓM HIỆU ỨNG ======================

class RageIncreaseCard : public Card {
private:
    int rageIncrease;
public:
    RageIncreaseCard(int increase = GameConfig::instance().getInt(ConfigKey::CARD_RAGE_GAIN));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};

class JackpotRollCard : public Card {
public:
    JackpotRollCard();
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};

class DoubleJackpotRollCard : public Card {
public:
    DoubleJackpotRollCard();
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};
