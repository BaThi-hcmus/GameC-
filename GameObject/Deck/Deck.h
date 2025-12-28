#pragma once
#include "../Card/DamageCard.h"
#include "../Card/StunAttackCard.h"
#include "../Card/PierceAttackCard.h"
#include "../Card/DodgeCard.h"
#include "../Card/ReduceDamageCard.h"
#include "../Card/ShieldCard.h"
#include "../Card/RageIncreaseCard.h"
#include "../Card/JackpotRollCard.h"
#include "../Card/DoubleJackpotRollCard.h"
#include "../NewGameConfig/GameConfig.h"

#include <vector>
#include <memory>
#include <unordered_set>
#include <functional>

using namespace std;

enum class CardType {
    DAMAGE,
    PIERCE,
    STUN_ATTACK,

    SHIELD,
    DODGE,
    REDUCE_DAMAGE,

    RAGE_INCREASE,
    JACKPOT_ROLL,
    DOUBLE_JACKPOT_ROLL
};

// cấu trúc mô hả luật sinh bài 
struct CardEntry {
    CardType type;                                // Loại logic
    int weight;                                  // Trọng số (xác suất)
    function<unique_ptr<Card>()> factory;        // Hàm tạo card
};

class Deck {
public :
    Deck();

    inline static const int HAND_SIZE = 6;

    // danh sách các lá bài không được phép xuất hiện hơn 1 lần
    static const unordered_set<CardType> _noDuplicateTypes;

    // các loại bài trong tay hiện tại => check lá bài trùng
    static unordered_set<CardType> _pickedInHand;

    // danh sách các luật rút bài 
    static vector<CardEntry> _cardPool;

    // lưu tổng xác suất
    static int _totalWeight;

    static unique_ptr<Card> drawCard();
    void startNewHand();
};