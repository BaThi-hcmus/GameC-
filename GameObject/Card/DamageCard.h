#pragma once
#include "Card.h"
#include "../NewGameConfig/GameConfig.h"

class StateNewGame;

using namespace std;

class DamageCard : public Card {
private:
    int _damageAmount;
public:
    DamageCard(int dmg = GameConfig::instance().getInt(ConfigKey::CARD_DAMAGE_NORMAL));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};