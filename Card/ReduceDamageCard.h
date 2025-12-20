#pragma once
#include "Card.h"
#include "../NewGameConfig/GameConfig.h"

class StateNewGame;

using namespace std;

class ReduceDamageCard : public Card {
private:
    float _reductionRatio;
public:
    ReduceDamageCard(float ratio = GameConfig::instance().getFloat(ConfigKey::CARD_DAMAGE_REDUCTION_RATIO));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};