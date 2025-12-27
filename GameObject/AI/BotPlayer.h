#pragma once

#include "../Player/Player.h"
#include "../Card/Card.h"
#include "../BattleSystem/BattleSystem.h"

#include <vector>
#include <memory>
#include <string>

using namespace std;

class BotPlayer : public Player {
protected:
    std::string _botName;
    int _turnCounter;

public:
    BotPlayer(std::string name);
    virtual ~BotPlayer();

    std::string getName() const override;
    bool isBot() const override;

    virtual void onTurnStart();
    std::vector<Card*> pickCards(const std::vector<std::unique_ptr<Card>>& hand) override;

    virtual bool hasSpecialSkillReady();
    virtual void executeSpecialSkill(Player& target, BattleSystem& battle);
    virtual void onOpponentAllocatedEnergy(Player& opponent, EffectScheduler& scheduler);
    virtual void applyPassiveIfActive(EffectScheduler& scheduler);
    virtual string getInfo() ;
};
