#pragma once
#include "Card.h"
#include "../NewGameConfig/GameConfig.h"

class StateNewGame;

using namespace std;

class StunAttackCard : public Card {
private:
    int _damageAmount;
public:
    StunAttackCard(int dmg = GameConfig::instance().getInt(ConfigKey::CARD_DAMAGE_STUN));
    void execute(Player& self, Player& target, StateNewGame& state) override;
    void printDescription() const override;
};