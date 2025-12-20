#pragma once
class Player;
#include "StatusEffect.h"
#include "ScheduledEffect.h"
#include <vector>
#include <memory>

class EffectScheduler {
private:
    vector<ScheduledEffect> _scheduledEffects;
public:
    vector<ScheduledEffect>& getScheduledEffects() {
        return _scheduledEffects;
    }

    void setScheduledEffects(ScheduledEffect scheduledEffect) {
        _scheduledEffects.push_back(move(scheduledEffect));
    }
public:
    void addEffect(Player* target, unique_ptr<StatusEffect> eff, TriggerType trigger, int duration) {
        //_scheduledEffects.push_back({target, move(eff), trigger, duration});
        setScheduledEffects({target, move(eff), trigger, duration});
    }

    // gọi khi event xảy ra
    void processTrigger(TriggerType trigger, Player& currentPlayer, Damage* damage = nullptr) {
        for (auto it = _scheduledEffects.begin(); it != _scheduledEffects.end();) {
            if (it->trigger == trigger && it->target == &currentPlayer) {
                it->effect->onApply(*it->target, damage); // effect tự định nghĩa hành vi
            }
            ++it;
        }
    }

    bool hasEffect(Player* target, EffectTag tag) {
        for (const auto& se : _scheduledEffects) {
            if (se.target == target && se.effect->hasTag(tag)) {
                return true;
            }
        }
        return false;
    }

    void tickPlayer(Player& p) {
        for (auto it = _scheduledEffects.begin(); it != _scheduledEffects.end(); ) {
            if (it->target == &p) {
                it->effect->tick();

                if (it->effect->isExpired()) {
                    it = _scheduledEffects.erase(it);
                    continue;
                }
            }
            ++it;
        }
    }

};
