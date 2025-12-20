#pragma once
#include "../Player/Player.h"
#include "../Effect/EffectScheduler.h"
#include "../Effect/ScheduledEffect.h"
#include "../NewGameConfig/GameConfig.h"
#include "../Damage/Damage.h"
#include <iostream>

using namespace std;

class BattleSystem {
private:
    EffectScheduler& _scheduler;
    int computeAttackDamage(Player& attacker, int baseDamage);
public:
    BattleSystem(EffectScheduler& scheduler) //scheduler : quản lí danh sách và vòng đời các hiệu ứng 
        : _scheduler(scheduler) {}

    void onTurnStart(Player& current) {
        _scheduler.processTrigger(TriggerType::onTurnStart, current);
    }

    void onTurnEnd(Player& current) {
        _scheduler.processTrigger(TriggerType::onTurnEnd, current);
    }

    void attack(Player& attacker, Player& defender, Damage& dmg);

    void rollJackpot(Player& roller, Player& target, int times);
    void activateJackpot(Player& roller, Player& target);
};
