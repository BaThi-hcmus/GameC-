#include "DoubleJackpotRollCard.h"
#include "../StateNewGame.h"
#include "../BattleSystem/BattleSystem.h"

#include <iostream>
#include <format>

using namespace std;

DoubleJackpotRollCard::DoubleJackpotRollCard()
    : Card("Quay Jackpot (2 lan)", CardCategory::Effect) {}

void DoubleJackpotRollCard::execute(Player& self, Player& target, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", _name);
    state.getBattle()->rollJackpot(self, target, 2);
}

void DoubleJackpotRollCard::printDescription() const {
    cout << "- Quay Jackpot 2 lan.\n";
}
