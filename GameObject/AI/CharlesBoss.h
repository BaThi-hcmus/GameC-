#pragma once
#include "BotPlayer.h"
#include "../Effect/DodgeEffect.h"

class CharlesBoss : public BotPlayer {
public:
    CharlesBoss();

    void onTurnStart() override;
    void applyPassiveIfActive(EffectScheduler& scheduler) override;
    void allocateCursedEnergy() override;
    string getInfo() override;
};
