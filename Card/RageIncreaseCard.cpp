#include "RageIncreaseCard.h"
#include "../Player/Player.h"
#include <iostream>
#include <format>

using namespace std;

RageIncreaseCard::RageIncreaseCard(int increase)
    : Card(format("Tang {} diem No II", increase), CardCategory::Effect),
      _rageIncrease(increase) {}

void RageIncreaseCard::execute(Player& self, Player&, StateNewGame&) {
    cout << format("\n>>>> Su dung la bai: {} \n", _name);
    self.increaseRage(_rageIncrease);
}

void RageIncreaseCard::printDescription() const {
    cout << format("- Tang {} diem no II.", _rageIncrease) << endl;
}
