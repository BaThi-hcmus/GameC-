#pragma once
#include "Card.h"
#include "../NewGameConfig/GameConfig.h"

class StateNewGame;

using namespace std;

class PierceAttackCard : public Card {
private:
    int _damageAmount;
public:
    PierceAttackCard(int dmg = GameConfig::instance().getInt(ConfigKey::CARD_DAMAGE_PIERCE));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};