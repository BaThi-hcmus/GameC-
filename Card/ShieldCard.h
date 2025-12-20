#pragma once
#include "Card.h"
#include "../NewGameConfig/GameConfig.h"

class StateNewGame;

using namespace std;

class ShieldCard : public Card {
private:
    int _shieldAmount;
public:
    ShieldCard(int shield = GameConfig::instance().getInt(ConfigKey::CARD_SHIELD_GAIN));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};