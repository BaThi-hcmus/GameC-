#pragma once
#include "Card.h"
#include "Player.h"
#include "GameConfig.h"
#include "Effect/StunEffect.h"
#include "Effect/DamageReductionEffect.h"
#include "Effect/DodgeEffect.h"

#include <iostream>
#include <format>

using namespace std;

// =============== NHÓM GÂY SÁT THƯƠNG ===================

/**
 * @brief Mặc định gây 200 sát thương cơ bản lên đối thủ.
 * Sát thương thực tế sẽ được Player xử lý
 * dựa trên chú lực tấn công, chí mạng, phòng thủ.
 */
class DamageCard : public Card {
private:
    int damageAmount;
public:
    DamageCard(int dmg = GameConfig::instance().getInt(ConfigKey::CARD_DAMAGE_NORMAL))
        : Card(format("Tan Cong Thuong ({} dame)", dmg), CardCategory::Damage), damageAmount(dmg) {}

    void execute(Player& self, Player& target) override {
        cout << format(">>  Su dung la bai: {} ", name);
        target.receiveAttack(damageAmount, self);
    }

    void printDescription() const override {
        cout << format("- {} : Gay {} sat thuong co ban.", name, damageAmount) << endl;
    }
};

/**
 * @brief Mặc định gây 50 damage và làm choáng đối thủ 1 lượt tiếp theo.
 */
class StunAttackCard : public Card {
private:
    int damageAmount;
public:
    StunAttackCard(int dmg = GameConfig::instance().getInt(ConfigKey::CARD_DAMAGE_STUN))
        : Card(format("Tan Cong Gay Choang ({} dame, gay choang doi thu 1 luot)", dmg), CardCategory::Damage), damageAmount(dmg) {}

    void execute(Player& self, Player& target) override {
        cout << format(">> Su dung la bai: {} ", name);
        target.receiveAttack(damageAmount, self);
        target.addEffect(std::make_unique<StunEffect>(1));

        cout << "!! Doi thu bi CHOANG trong 1 luot toi!" << endl;
    }

    void printDescription() const override {
        cout << format("- {} : {} dame + choang 1 luot.", name, damageAmount) << endl;
    }
};

/**
 * @brief Tấn công xuyên giáp, mắc định 150 damage – bỏ qua shield.
 */
class PierceAttackCard : public Card {
private : 
    int damageAmount;
public:
    PierceAttackCard(int dmg = GameConfig::instance().getInt(ConfigKey::CARD_DAMAGE_PIERCE))
        : Card(format("Tan Cong Pha Giap ({} dame)", dmg), CardCategory::Damage), damageAmount(dmg) {}

    void execute(Player& self, Player& target) override {
        cout << format(">> Su dung la bai: {} ", name);
        target.receivePierceAttack(damageAmount, self);
    }

    void printDescription() const override {
        cout << format("- {} : Tan cong xuyen giap.", name) << endl;
    }
};

// ================= NHÓM PHÒNG THỦ ======================

/**
 * @brief Cộng thêm mặc định 50 shield cho Hakari.
 */
class ShieldCard_50 : public Card {
private:
    int shieldAmount;
public:
    ShieldCard_50(int shield = GameConfig::instance().getInt(ConfigKey::CARD_SHIELD_GAIN))
        : Card(format("Phong Thu Thuong (+{} shield)", shield), CardCategory::Defense), shieldAmount(shield) {}

    void execute(Player& self, Player& target) override {
        cout << format(">> Su dung la bai: {} ", name);
        self.addShield(shieldAmount);
    }

    void printDescription() const override {
        cout << format("- {} : Tang {} shield.", name, shieldAmount) << endl;
    }
};

/**
 * @brief Giảm 50% sát thương nhận trong lượt này.
 */
class ReduceDamageCard : public Card {
private:
    float reductionRatio;
public:
    ReduceDamageCard(float ratio = GameConfig::instance().getFloat(ConfigKey::CARD_DAMAGE_REDUCTION_RATIO))
        : Card(format("Giam {}% sat thuong nhan vao", ratio * 100), CardCategory::Defense), reductionRatio(ratio) {}

    void execute(Player& self, Player& target) override {
        cout << ">> Su dung la bai kich hoat phong thu giam sat thuong!" << endl;
        self.addEffect(
            std::make_unique<DamageReductionEffect>(reductionRatio, 1)
        );
    }

    void printDescription() const override {
        cout << format("- Giam {}% sat thuong nhan vao.", reductionRatio * 100) << endl;
    }
};

/**
 * @brief 60% né tránh toàn bộ đòn tấn công.
 */
class DodgeCard : public Card {
private:
    float dodgeChance;
public:
    DodgeCard(float chance = GameConfig::instance().getFloat(ConfigKey::CARD_DODGE_CHANCE))
        : Card(format("Ne Tranh {}%", chance * 100), CardCategory::Defense), dodgeChance(chance) {}

    void execute(Player& self, Player& target) override {
        cout << ">> Su dung la bai kich hoat phong thu ne tranh!" << endl;
        self.addEffect(
            std::make_unique<DodgeEffect>(dodgeChance, 1)
        );
    }

    void printDescription() const override {
        cout << format("- {}% ne don tan cong.", dodgeChance * 100) << endl;
    }
};

// ================== NHÓM HIỆU ỨNG ======================

/**
 * @brief Tăng 3 điểm nộ ii.
 */
class RageIncreaseCard : public Card {
private:
    int rageIncrease;
public:
    RageIncreaseCard(int increase = GameConfig::instance().getInt(ConfigKey::CARD_RAGE_GAIN))
        : Card(format("Tang {} diem No II", increase), CardCategory::Effect), rageIncrease(increase) {}

    void execute(Player& self, Player& target) override {
        cout << format(">> Su dung la bai tang no II!") << endl;
        self.increaseRage(rageIncrease);
    }

    void printDescription() const override {
        cout << format("- Tang {} diem no II.", rageIncrease) << endl;
    }
};

/**
 * @brief Quay Jackpot 1 lần.
 */
class JackpotRollCard : public Card {
public:
    JackpotRollCard()
        : Card("Quay Jackpot (1 lan)", CardCategory::Effect) {}

    void execute(Player& self, Player& target) override {
        cout << ">> Su dung la bai quay JACKPOT!" << endl;
        self.rollJackpot(1, target);
    }

    void printDescription() const override {
        cout << "- Quay Jackpot 1 lan." << endl;
    }
};

/**
 * @brief Quay Jackpot 2 lần.
 */
class DoubleJackpotRollCard : public Card {
public:
    DoubleJackpotRollCard()
        : Card("Quay Jackpot (2 lan)", CardCategory::Effect) {}

    void execute(Player& self, Player& target) override {
        cout << ">> Su dung la bai quay JACKPOT x2!!!" << endl;
        self.rollJackpot(2, target);
    }

    void printDescription() const override {
        cout << "- Quay Jackpot 2 lan." << endl;
    }
};
