#pragma once
#include "BotPlayer.h"
#include "../Damage/PiercingDamage.h"

class KashimoBoss : public BotPlayer {
public:
    KashimoBoss();

    void onTurnStart() override;
    bool hasSpecialSkillReady() override;
    void executeSpecialSkill(Player& target, BattleSystem& battle) override;
    void allocateCursedEnergy() override;
    string getInfo() override;
};
