#pragma once
#include "BotPlayer.h"
#include "../Effect/StunEffect.h"

class UraumeBoss : public BotPlayer {
public:
    UraumeBoss();

    void onTurnStart() override;
    void onOpponentAllocatedEnergy(Player& opponent, EffectScheduler& scheduler) override;
    void allocateCursedEnergy() override;
    string getInfo() override ;
    
};
