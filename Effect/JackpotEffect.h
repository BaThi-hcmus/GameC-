#pragma once
#include "StatusEffect.h"
#include "../Player.h"

using namespace std;

class JackpotEffect : public StatusEffect {
private:
    int buffTurns;  // số lượt có buff thật sự
    bool firstApply = true;      
public:
    JackpotEffect(int buffTurns)
        : StatusEffect(buffTurns + 1), // +1 lượt cooldown
          buffTurns(buffTurns) {}

    void onApply(Player& p, Damage* dmg = nullptr) override {
        int turnsLeft = duration;

        // Nếu đã qua giai đoạn buff → chỉ còn cooldown
        if (turnsLeft <= 1) {
            std::cout << "[JACKPOT] Cooldown (no buff)\n";
            return;
        }

        // nếu được kích hoạt trong lượt thì chỉ áp dụng hồi đầy thanh máu
        // if(firstApply == true) {
        //     std::cout << "Ban duoc hoi day HP\n";
        //     firstApply = false;
        //     p.hp = Player::MAX_HP;
        //     return;
        // }

        // các lượt buff thực sự
        p.hp = Player::MAX_HP;
        p.attackEnergy = Player::MAX_CURSED_ENERGY;
        p.defenseEnergy = 0;
        p.jackpotEnergy = 0;

        std::cout << "[JACKPOT] Full HP + Auto Attack Energy\n";
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::Jackpot;
    }
};
