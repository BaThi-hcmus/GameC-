#pragma once 
class Player; 
#include "StatusEffect.h"
#include "../Damage/Damage.h"
#include <memory>

enum class TriggerType {
    onTurnStart,
    onTurnEnd,
    onAfterReceiveDamage,
    onBeforeReceiveDamage,
    onBeforeDealDamage
};

struct ScheduledEffect {
    Player* target;     // hiệu ứng tác động vào ai
    unique_ptr<StatusEffect> effect;   
    TriggerType trigger;    // tác động vào thời điểm nào 
    int remainingTurns; // số lượt còn lại
};
