#include "KashimoBoss.h"
#include <iostream>

KashimoBoss::KashimoBoss()
    : BotPlayer("Kashimo Hajime") {
    setHp(2500);
}

void KashimoBoss::onTurnStart() {
    std::cout << "\n>> [BOSS KASHIMO] +9 Rage!\n";
    BotPlayer::onTurnStart();
    increaseRage(9);
}

bool KashimoBoss::hasSpecialSkillReady() {
    return getRage() >= Player::MAX_RAGE;
}

void KashimoBoss::executeSpecialSkill(Player& target, BattleSystem& battle) {
    auto dmg = std::make_unique<PiercingDamage>();
    dmg->setAmount(400);
    battle.attack(*this, target, *dmg);
    setRage(0);
}

void KashimoBoss::allocateCursedEnergy() {
    _attackEnergy = 5;
    _defenseEnergy = 0;
    _jackpotEnergy = 0;
}

string KashimoBoss::getInfo() {
    return "[BOSS KASHIMO] Moi luot tang 9 diem no II. Khi thanh no day thi gay sat thuong xuyen giap voi 400 damage\n";
}
