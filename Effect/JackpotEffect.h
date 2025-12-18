#pragma once
#include "StatusEffect.h"
#include "../Player.h"

using namespace std;

class JackpotEffect : public StatusEffect {
private:
    int buffTurns;        // số lượt có buff thật sự
public:
    JackpotEffect(int buffTurns)
        : StatusEffect(buffTurns + 1), // +1 lượt cooldown
          buffTurns(buffTurns) {}

    void onTurnStart(Player& p) override {
        int turnsLeft = duration;

        // Nếu đã qua giai đoạn buff → chỉ còn cooldown
        if (turnsLeft <= 1) {
            std::cout << "[JACKPOT] Cooldown (no buff)\n";
            return;
        }

        // các lượt buff thực sự
        p.hp = Player::MAX_HP;
        p.attackEnergy = Player::MAX_CURSED_ENERGY;
        p.defenseEnergy = 0;
        p.jackpotEnergy = 0;

        std::cout << "[JACKPOT] Full HP + Auto Attack Energy\n";
    }

    void onApply(Player& p) {
        cout << "[JACKPOT] Full HP luot hien tai\n";
        p.hp = Player::MAX_HP;
    }

    void onRemove(Player&) override {
        std::cout << "[JACKPOT] Cooldown ket thuc, ban co the quay jackpot\n";
    }

    bool hasTag(EffectTag tag) override {
        return tag == EffectTag::Jackpot;
    }
};
