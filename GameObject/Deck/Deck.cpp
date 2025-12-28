#include "Deck.h"
#include <iostream>
#include <unordered_set>
#include <vector>
#include <functional>
#include <cstdlib>

const unordered_set<CardType> Deck::_noDuplicateTypes = {
    CardType::DODGE,
    CardType::REDUCE_DAMAGE,
    CardType::STUN_ATTACK,
    CardType::RAGE_INCREASE,
    CardType::JACKPOT_ROLL,
    CardType::DOUBLE_JACKPOT_ROLL
};

unordered_set<CardType> Deck::_pickedInHand;

//các luật sinh bài 
vector<CardEntry> Deck::_cardPool = {

    // ========== ATTACK ==========
    { CardType::DAMAGE,        80, [](){ return make_unique<DamageCard>(); } },
    { CardType::PIERCE,        50, [](){ return make_unique<PierceAttackCard>(); } },
    { CardType::STUN_ATTACK,   20, [](){ return make_unique<StunAttackCard>(); } },

    // ========== EFFECT ==========
    { CardType::SHIELD,        40, [](){ return make_unique<ShieldCard>(); } },
    { CardType::DODGE,         50, [](){ return make_unique<DodgeCard>(); } },
    { CardType::REDUCE_DAMAGE, 40, [](){ return make_unique<ReduceDamageCard>(); } },

    // ========== JACKPOT =========
    { CardType::RAGE_INCREASE,        50, [](){ return make_unique<RageIncreaseCard>(); } },
    { CardType::JACKPOT_ROLL,         40, [](){ return make_unique<JackpotRollCard>(); } },
    { CardType::DOUBLE_JACKPOT_ROLL,  15, [](){ return make_unique<DoubleJackpotRollCard>(); } }
};

// tính tổng trọng số xác suất
int Deck::_totalWeight = [](){
    int sum = 0;
    for (auto& e : _cardPool) sum += e.weight;
    return sum;
}();

Deck::Deck() {
    // do nothing
}

void Deck::startNewHand() {
    _pickedInHand.clear();
}

unique_ptr<Card> Deck::drawCard() {
    for (int attempt = 0; attempt < 100; ++attempt) {

        int roll = rand() % _totalWeight;
        int acc = 0;

        for (const auto& entry : _cardPool) {
            acc += entry.weight;

            if (roll < acc) {

                // Nếu loại này bị cấm trùng & đã xuất hiện → bỏ
                if (_noDuplicateTypes.count(entry.type) &&
                    _pickedInHand.count(entry.type)) {
                    break; // thử lại attempt khác
                }

                // Đánh dấu đã xuất hiện 
                if (_noDuplicateTypes.count(entry.type)) {
                    _pickedInHand.insert(entry.type);
                }

                // Tạo card thật
                auto card = entry.factory();

                cout << "[DECK] Rut duoc la bai: "
                     << card->_name << endl;

                return card;
            }
        }
    }

    // mặc định trả về thẻ tấn công thường
    return make_unique<DamageCard>();
}

