#include "PierceAttackCard.h"
#include "../StateNewGame.h"
#include "../BattleSystem/BattleSystem.h"
#include "../Damage/PiercingDamage.h"

#include <iostream>
#include <format>

using namespace std;

PierceAttackCard::PierceAttackCard(int dmg)
    : Card(format("Tan Cong Pha Giap ({} dame)", dmg), CardCategory::Damage),
      _damageAmount(dmg) {}

void PierceAttackCard::execute(Player& self, Player& target, StateNewGame& state) {
    cout << format("\n>>>> Su dung la bai: {} \n", _name);
    cout << "Damage duoc tru thang vao Hp cua doi thu\n";

    auto dmg = make_unique<PiercingDamage>();
    dmg->setAmount(_damageAmount);
    
    state.getBattle()->attack(self, target, *dmg);
}

void PierceAttackCard::printDescription() const {
    cout << "- Tan cong xuyen giap.\n";
}
