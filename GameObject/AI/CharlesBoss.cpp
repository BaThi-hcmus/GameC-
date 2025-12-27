#include "CharlesBoss.h"
#include <iostream>

CharlesBoss::CharlesBoss()
    : BotPlayer("Charles Bernard") {}

void CharlesBoss::onTurnStart() {
    BotPlayer::onTurnStart();
    if (_turnCounter > 0 && _turnCounter % 3 == 0) {
        std::cout << "\n>> [BOSS CHARLES] Charles da nhin thay tuong lai!\n";
    }
}

void CharlesBoss::applyPassiveIfActive(EffectScheduler& scheduler) {
    if (_turnCounter > 0 && _turnCounter % 3 == 0) {
        scheduler.addEffect(
            this,
            std::make_unique<DodgeEffect>(1, 1.0f, TickTrigger::endOfTurnOpponent),
            TriggerType::onBeforeReceiveDamage,
            1
        );
    }
}

void CharlesBoss::allocateCursedEnergy() {
    _attackEnergy = 2;
    _defenseEnergy = 3;
    _jackpotEnergy = 0;
}

string CharlesBoss::getInfo() {
    return "[BOSS CHARLES] cach nhau 3 luot cua ban than, BOSS se kich hoat hieu ung dodge trong 1 luot\n";
}
