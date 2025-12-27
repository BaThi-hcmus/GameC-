#include "BotHakari.h"
#include <cstdlib>

BotHakari::BotHakari()
    : BotPlayer("Hakari (CPU)") {}

void BotHakari::allocateCursedEnergy() {
    int roll = rand() % 10;
    if (roll < 3) {
        _attackEnergy = 0; _defenseEnergy = 0; _jackpotEnergy = 5;
    } else if (roll < 6) {
        _attackEnergy = 1; _defenseEnergy = 3; _jackpotEnergy = 1;
    } else {
        _attackEnergy = 4; _defenseEnergy = 1; _jackpotEnergy = 0;
    }
}

string BotHakari::getInfo() {
    return "";
}
