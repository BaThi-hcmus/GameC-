#pragma once
#include "StatusEffect.h"
#include "../Player/Player.h"

using namespace std;

class JackpotEffect : public StatusEffect {
private:
    int _buffTurns;  // số lượt có buff thật sự : 5, duration = 5 + 1 = 6
    bool firstApply = true;      
public:
    JackpotEffect(int buffTurns)
        : StatusEffect(buffTurns + 1), // +1 lượt cooldown
          _buffTurns(buffTurns) {}

    void onApply(Player& p, Damage* dmg = nullptr) override {
        int turnsLeft = _duration;

        // Nếu đã qua giai đoạn buff → chỉ còn cooldown
        if (turnsLeft <= 1) {
            cout << "[JACKPOT] Cooldown (no buff)\n";
            return;
        }

        // nếu được kích hoạt trong lượt thì chỉ áp dụng hồi đầy thanh máu
        if(firstApply == true) {
            cout << "Ban duoc hoi day HP trong luot nay\n";
            firstApply = false;
            p.setHp(Player::MAX_HP);
            return;
        }

        // các lượt buff thực sự
        p.setHp(Player::MAX_HP);
        p.setAttackEnergy(Player::MAX_CURSED_ENERGY);
        p.setDefenseEnergy(0);
        p.setJackpotEnergy(0);
        cout << "[JACKPOT] Full HP + Auto Attack Energy\n";
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::Jackpot;
    }
};
