#pragma once
#include "Player.h"
#include "Effect/EffectScheduler.h"
#include "Effect/ScheduledEffect.h"
#include "GameConfig.h"
#include "Damage/Damage.h"
#include <iostream>

class BattleSystem {
private:
    EffectScheduler& scheduler;
public:
    BattleSystem(EffectScheduler& scheduler) //scheduler : quản lí danh sách và vòng đời các hiệu ứng 
        : scheduler(scheduler) {}

    void onTurnStart(Player& current) {
        scheduler.processTrigger(TriggerType::onTurnStart, current);
    }

    void onTurnEnd(Player& current) {
        scheduler.processTrigger(TriggerType::onTurnEnd, current);
    }

    void attack(Player& attacker, Player& defender, Damage& dmg);

    void rollJackpot(Player& roller, Player& target, int times);
    void activateJackpot(Player& roller, Player& target);
private:
    int computeAttackDamage(Player& attacker, int baseDamage);
};
