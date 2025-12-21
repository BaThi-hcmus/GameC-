#pragma once
#include "Card.h"
#include "../NewGameConfig/GameConfig.h"

class StateNewGame;

using namespace std;

class DodgeCard : public Card {
private:
    float _dodgeChance;
public:
    DodgeCard(float chance = GameConfig::instance().getFloat(ConfigKey::CARD_DODGE_CHANCE));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};