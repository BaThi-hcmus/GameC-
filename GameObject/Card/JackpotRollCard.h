#pragma once
#include "Card.h"
#include "../NewGameConfig/GameConfig.h"

using namespace std;

class JackpotRollCard : public Card {
public:
    JackpotRollCard();
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};