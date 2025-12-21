#include "ShieldCard.h"
#include "../Player/Player.h"
#include <iostream>
#include <format>

ShieldCard::ShieldCard(int shield)
    : Card(format("Phong Thu Thuong (+{} shield)", shield), CardCategory::Defense),
      _shieldAmount(shield) {}

void ShieldCard::execute(Player& self, Player&, StateNewGame&) {
    cout << format("\n>>>> Su dung la bai: {} \n", _name);

    self.addShield(_shieldAmount);
}

void ShieldCard::printDescription() const {
    cout << format("- Tang {} shield.", _shieldAmount) << endl;
}
