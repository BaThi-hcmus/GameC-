#pragma once
#include "StatusEffect.h"
#include "../Player/Player.h"

using namespace std;

class JackpotEffect : public StatusEffect {
private:
    int _buffTurns;  // số lượt có buff thật sự : 5, duration = 5 + 1 = 6
    bool firstApply = true;      
public:
    JackpotEffect(int buffTurns, TickTrigger trigger)
        : StatusEffect(buffTurns + 1, trigger), // +1 lượt cooldown
          _buffTurns(buffTurns) {}

    void onApply(Player& p, Damage* dmg = nullptr) override {
        int turnsLeft = _duration;

        // Nếu đã qua giai đoạn buff → chỉ còn cooldown
        if (turnsLeft <= 1) {
            cout << "[JACKPOT] Cooldown (no buff)\n";
            return;
        }

        // nếu được kích hoạt trong lượt 
        if(firstApply == true) {
            firstApply = false;
            
            // CHECK NERF CỦA URAUME
            if (p.isJackpotNerfed()) {
                cout << "[URAUME EFFECT] Jackpot bi nguyen rua! Chi hoi 500 HP!\n";
                int newHp = min(Player::MAX_HP, p.getHp() + 500);
                p.setHp(newHp);
            } else {
                cout << "Ban duoc hoi day HP trong luot nay\n";
                p.setHp(Player::MAX_HP);
            }
            return;
        }

        // Buff các lượt sau (Uraume không chặn cái này theo mô tả, chỉ chặn hồi máu)
        // Nếu muốn chặn cả auto-full HP mỗi lượt thì thêm check ở đây
        if (p.isJackpotNerfed()) {
            // Logic nếu bị nerf thì mỗi lượt không hồi full mà chỉ hồi ít hoặc không hồi?
            // Theo mô tả của bạn: "sau mỗi lượt thanh máu reset về hiện tại + 500"
            int newHp = min(Player::MAX_HP, p.getHp() + 500);
            p.setHp(newHp);
            cout << "[URAUME EFFECT] Jackpot bi nguyen rua! Chi hoi 500 HP moi luot!\n";
        } else {
            p.setHp(Player::MAX_HP);
            cout << "[JACKPOT] Hoi day HP moi luot\n";
        }
        
        p.setAttackEnergy(Player::MAX_CURSED_ENERGY);
        p.setDefenseEnergy(0);
        p.setJackpotEnergy(0);
        cout << "[JACKPOT] auto attack energy\n";
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::Jackpot;
    }
};
