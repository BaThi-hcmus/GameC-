#include "ReduceDamageCard.h"
#include "../../GameState/StateNewGame.h"
#include "../Effect/DamageReductionEffect.h"

#include <iostream>
#include <format>

using namespace std;

ReduceDamageCard::ReduceDamageCard(float ratio)
    : Card(format("Giam {}% sat thuong nhan vao", ratio * 100), CardCategory::Defense),
      _reductionRatio(ratio) {}

void ReduceDamageCard::execute(Player& self, Player&, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", _name);

    state.getScheduler().addEffect(
        &self,
        make_unique<DamageReductionEffect>(1, _reductionRatio, TickTrigger::endOfTurnOpponent),
        TriggerType::onBeforeReceiveDamage,
        1
    );
}

void ReduceDamageCard::printDescription() const {
    cout << format("- Giam {}% sat thuong nhan vao.", _reductionRatio * 100) << endl;
}
