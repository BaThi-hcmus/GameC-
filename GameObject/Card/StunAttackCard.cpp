#include "StunAttackCard.h"
#include "../../GameState/StateNewGame.h"
#include "../BattleSystem/BattleSystem.h"
#include "../Effect/StunEffect.h"
#include "../Damage/NormalDamage.h"

#include <iostream>
#include <format>

StunAttackCard::StunAttackCard(int dmg)
    : Card(format("Tan Cong Gay Choang ({} dame)", dmg), CardCategory::Damage),
      _damageAmount(dmg) {}

void StunAttackCard::execute(Player& self, Player& target, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", _name);
    cout << "!! Doi thu bi CHOANG trong 1 luot toi!\n";

    auto dmg = make_unique<NormalDamage>();
    dmg->setAmount(_damageAmount);

    state.getBattle()->attack(self, target, *dmg);

    state.getScheduler().addEffect(
        &target,
        make_unique<StunEffect>(1, TickTrigger::endOfTurn),
        TriggerType::onTurnStart,
        1
    );
}

void StunAttackCard::printDescription() const {
    cout << format("- {} : {} dame + choang 1 luot.", _name, _damageAmount) << endl;
}
