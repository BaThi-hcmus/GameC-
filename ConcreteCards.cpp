#include "ConcreteCards.h"

#include "StateNewGame.h"
#include "BattleSystem.h"

#include "Effect/StunEffect.h"
#include "Effect/DamageReductionEffect.h"
#include "Effect/DodgeEffect.h"
#include "Damage/NormalDamage.h"
#include "Damage/PiercingDamage.h"

#include <iostream>
#include <format>

using namespace std;

// ================= DAMAGE =================

DamageCard::DamageCard(int dmg)
    : Card(format("Tan Cong Thuong ({} dame)", dmg), CardCategory::Damage),
      damageAmount(dmg) {}

void DamageCard::execute(Player& self, Player& target, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", name);

    // Tạo damage thường
    auto dmg = std::make_unique<NormalDamage>();
    dmg->amount = damageAmount;

    state.battle->attack(self, target, *dmg);
}

void DamageCard::printDescription() const {
    cout << format("- {} : Gay {} sat thuong co ban.", name, damageAmount) << endl;
}

// ================= STUN ATTACK =================

StunAttackCard::StunAttackCard(int dmg)
    : Card(format("Tan Cong Gay Choang ({} dame)", dmg), CardCategory::Damage),
      damageAmount(dmg) {}

void StunAttackCard::execute(Player& self, Player& target, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", name);
    cout << "!! Doi thu bi CHOANG trong 1 luot toi!\n";

    // Tạo damage thường
    auto dmg = std::make_unique<NormalDamage>();
    dmg->amount = damageAmount;

    state.battle->attack(self, target, *dmg);

    state.scheduler.addEffect(
        &target,
        std::make_unique<StunEffect>(1),
        TriggerType::onTurnStart,
        1
    );
}

void StunAttackCard::printDescription() const {
    cout << format("- {} : {} dame + choang 1 luot.", name, damageAmount) << endl;
}

// ================= PIERCE =================

PierceAttackCard::PierceAttackCard(int dmg)
    : Card(format("Tan Cong Pha Giap ({} dame)", dmg), CardCategory::Damage),
      damageAmount(dmg) {}

void PierceAttackCard::execute(Player& self, Player& target, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", name);
    cout << "Damage duoc tru thang vao Hp cua doi thu\n";

    // Tạo damage xuyên giáp
    auto dmg = std::make_unique<PiercingDamage>();
    dmg->amount = damageAmount;

    state.battle->attack(self, target, *dmg);
    //target.receivePierceAttack(damageAmount, self);
}

void PierceAttackCard::printDescription() const {
    cout << "- Tan cong xuyen giap.\n";
}

// ================= SHIELD =================

ShieldCard_50::ShieldCard_50(int shield)
    : Card(format("Phong Thu Thuong (+{} shield)", shield), CardCategory::Defense),
      shieldAmount(shield) {}

void ShieldCard_50::execute(Player& self, Player&, StateNewGame&) {
    cout << format("\n>>>> Su dung la bai: {} \n", name);

    self.addShield(shieldAmount);
}

void ShieldCard_50::printDescription() const {
    cout << format("- Tang {} shield.", shieldAmount) << endl;
}

// ================= REDUCE DAMAGE =================

ReduceDamageCard::ReduceDamageCard(float ratio)
    : Card(format("Giam {}% sat thuong nhan vao", ratio * 100), CardCategory::Defense),
      reductionRatio(ratio) {}

void ReduceDamageCard::execute(Player& self, Player&, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", name);

    state.scheduler.addEffect(
        &self,
        std::make_unique<DamageReductionEffect>(reductionRatio, 1),
        TriggerType::onAfterReceiveDamage,
        1
    );
}

void ReduceDamageCard::printDescription() const {
    cout << format("- Giam {}% sat thuong nhan vao.", reductionRatio * 100) << endl;
}

// ================= DODGE =================

DodgeCard::DodgeCard(float chance)
    : Card(format("Ne Tranh {}%", chance * 100), CardCategory::Defense),
      dodgeChance(chance) {}

void DodgeCard::execute(Player& self, Player&, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", name);

    state.scheduler.addEffect(
        &self,
        std::make_unique<DodgeEffect>(dodgeChance, 1),
        TriggerType::onBeforeReceiveDamage,
        1
    );
}

void DodgeCard::printDescription() const {
    cout << format("- {}% ne don.", dodgeChance * 100) << endl;
}

// ================= RAGE =================

RageIncreaseCard::RageIncreaseCard(int increase)
    : Card(format("Tang {} diem No II", increase), CardCategory::Effect),
      rageIncrease(increase) {}

void RageIncreaseCard::execute(Player& self, Player&, StateNewGame&) {
    cout << format("\n>>>> Su dung la bai: {} \n", name);

    self.increaseRage(rageIncrease);
}

void RageIncreaseCard::printDescription() const {
    cout << format("- Tang {} diem no II.", rageIncrease) << endl;
}

// ================= JACKPOT =================

JackpotRollCard::JackpotRollCard()
    : Card("Quay Jackpot (1 lan)", CardCategory::Effect) {}

void JackpotRollCard::execute(Player& self, Player& target, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", name);

    state.battle->rollJackpot(self, target, 1);
}

void JackpotRollCard::printDescription() const {
    cout << "- Quay Jackpot 1 lan.\n";
}

DoubleJackpotRollCard::DoubleJackpotRollCard()
    : Card("Quay Jackpot (2 lan)", CardCategory::Effect) {}

void DoubleJackpotRollCard::execute(Player& self, Player& target, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", name);
    
    state.battle->rollJackpot(self, target, 2);
}

void DoubleJackpotRollCard::printDescription() const {
    cout << "- Quay Jackpot 2 lan.\n";
}
