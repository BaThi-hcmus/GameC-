#include "JackpotRollCard.h"
#include "../../GameState/StateNewGame.h"
#include "../BattleSystem/BattleSystem.h"

#include <iostream>
#include <format>

using namespace std;

JackpotRollCard::JackpotRollCard()
    : Card("Quay Jackpot (1 lan)", CardCategory::Effect) {}

void JackpotRollCard::execute(Player& self, Player& target, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", _name);
    state.getBattle()->rollJackpot(self, target, 1);
}

void JackpotRollCard::printDescription() const {
    cout << "- Quay Jackpot 1 lan.\n";
}
