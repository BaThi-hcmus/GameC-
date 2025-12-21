#pragma once
#include "Card.h"
#include "../NewGameConfig/GameConfig.h"

class StateNewGame;

using namespace std;

class RageIncreaseCard : public Card {
private:
    int _rageIncrease;
public:
    RageIncreaseCard(int increase = GameConfig::instance().getInt(ConfigKey::CARD_RAGE_GAIN));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};