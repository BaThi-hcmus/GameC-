#pragma once
class Player;
#include "StatusEffect.h"
#include "ScheduledEffect.h"
#include <vector>
#include <memory>

class EffectScheduler {
public:
    std::vector<ScheduledEffect> scheduledEffects;

    void addEffect(Player* target, std::unique_ptr<StatusEffect> eff, TriggerType trigger, int duration) {
        scheduledEffects.push_back({target, std::move(eff), trigger, duration});
    }

    // gọi khi event xảy ra
    void processTrigger(TriggerType trigger, Player& currentPlayer, Damage* damage = nullptr) {
        for (auto it = scheduledEffects.begin(); it != scheduledEffects.end();) {
            if (it->trigger == trigger && it->target == &currentPlayer) {
                it->effect->onApply(*it->target, damage); // effect tự định nghĩa hành vi
            }
            ++it;
        }
    }

    bool hasEffect(Player* target, EffectTag tag) {
        for (const auto& se : scheduledEffects) {
            if (se.target == target && se.effect->hasTag(tag)) {
                return true;
            }
        }
        return false;
    }

    void tickPlayer(Player& p) {
        for (auto it = scheduledEffects.begin(); it != scheduledEffects.end(); ) {
            if (it->target == &p) {
                it->effect->tick();

                if (it->effect->isExpired()) {
                    it = scheduledEffects.erase(it);
                    continue;
                }
            }
            ++it;
        }
    }

};
