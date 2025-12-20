#pragma once
#include "Card.h"
#include "../NewGameConfig/GameConfig.h"

class StateNewGame;

using namespace std;

class DoubleJackpotRollCard : public Card {
public:
    DoubleJackpotRollCard();
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};