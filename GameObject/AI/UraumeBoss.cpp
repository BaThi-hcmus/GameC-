#include "UraumeBoss.h"
#include <iostream>
#include <string>

UraumeBoss::UraumeBoss()
    : BotPlayer("Uraume") {
    setHp(3000);
}

void UraumeBoss::onTurnStart() {
    std::cout << "\n>> [BOSS URAUME] +18 Rage!\n";
    BotPlayer::onTurnStart();
    increaseRage(18);
}

void UraumeBoss::onOpponentAllocatedEnergy(Player& opponent, EffectScheduler& scheduler) {
    if (getRage() >= Player::MAX_RAGE && opponent.getAttackEnergy() > 1) {
        scheduler.addEffect(
            &opponent,
            std::make_unique<StunEffect>(1, TickTrigger::endOfTurn),
            TriggerType::onTurnStart,
            1
        );
        setRage(0);
    }
}

void UraumeBoss::allocateCursedEnergy() {
    _attackEnergy = 2;
    _defenseEnergy = 3;
    _jackpotEnergy = 0;
}

string UraumeBoss::getInfo() {
    string str = "[BOSS URAUME] Moi luot tang 18 diem no II. Khi thanh no day kich hoat hieu ung dodge trong 1 luot\n"
                    "Giam hieu ung Jackpot cua doi thu: moi luot chi duoc hoi 500 HP\n";
    return str;
}
