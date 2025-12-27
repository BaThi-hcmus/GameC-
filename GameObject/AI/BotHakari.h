#pragma once
#include "BotPlayer.h"

class BotHakari : public BotPlayer {
public:
    BotHakari();
    void allocateCursedEnergy() override;
    string getInfo() override ;
};
