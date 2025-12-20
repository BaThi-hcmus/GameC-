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

using namespace std;

/**
 * @brief Lớp Deck quản lý toàn bộ bộ bài của Hakari.
 * - Chịu trách nhiệm khởi tạo bộ bài gốc
 * - Xáo trộn
 * - Rút bài ngẫu nhiên
 * - Refill khi bài gần hết
 */
class Deck {
private:
    /**
     * @brief Danh sách các lá bài hiện có trong Deck.
     * Sử dụng unique_ptr để quản lý vòng đời Card an toàn.
     */
    vector<unique_ptr<Card>> _Deck;

    /**
     * @brief Tổng số lá bài chuẩn trong Deck.
     * Phải KHỚP với số lượng khởi tạo trong initializeFullDeck().
     */
    const int INITIAL_DECK_SIZE = GameConfig::instance().getInt(ConfigKey::DECK_INITIAL_SIZE);

    /**
     * @brief Tạo lại toàn bộ bộ bài theo luật game.
     * Hàm này được dùng khi:
     * - Khởi tạo Deck
     * - Refill Deck khi gần hết bài
     */
    void initializeFullDeck();

public:
    Deck();

    /**
     * @brief Xáo trộn thứ tự các lá bài trong Deck.
     */
    void shuffle();

    /**
     * @brief Rút 1 lá bài ngẫu nhiên từ Deck.
     * @return unique_ptr<Card> – lá bài đã rút (nullptr nếu Deck rỗng)
     */
    unique_ptr<Card> drawCard();

    /**
     * @brief Kiểm tra và refill Deck nếu số bài dưới ngưỡng. mắc định dưới 10 lá.
     * @param threshold Số bài tối thiểu cho phép
     */
    void checkAndRefillDeck(int threshold = GameConfig::instance().getInt(ConfigKey::DECK_MIN_SIZE));

    /**
     * @brief Lấy số lượng bài hiện tại trong Deck.
     */
    int size() const { return static_cast<int>(_Deck.size()); }
};
