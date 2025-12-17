#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <format>

using namespace std;

/**
 * @brief Constructor của Deck.
 * Khởi tạo Deck và xáo trộn ngay từ đầu game.
 */
Deck::Deck() {
    initializeFullDeck(); // Tạo bộ bài đầy đủ
    shuffle(); // Xáo trộn bộ bài

    cout << format("[DECK] Khoi tao bo bai voi {} la bai.", m_Deck.size()) << endl;
}

/**
 * @brief Khởi tạo toàn bộ lá bài theo đúng ConcreteCards.h
 */
void Deck::initializeFullDeck() {
    //Xóa hết bài cũ
    m_Deck.clear();

    // ================== DAMAGE ==================
    for (int i = 0; i < 6; ++i)
        m_Deck.push_back(make_unique<DamageCard>());

    for (int i = 0; i < 4; ++i)
        m_Deck.push_back(make_unique<StunAttackCard>());

    for (int i = 0; i < 4; ++i)
        m_Deck.push_back(make_unique<PierceAttackCard>());

    // ================== DEFENSE =================
    for (int i = 0; i < 4; ++i)
        m_Deck.push_back(make_unique<ShieldCard_50>());

    for (int i = 0; i < 3; ++i)
        m_Deck.push_back(make_unique<ReduceDamageCard>());

    for (int i = 0; i < 3; ++i)
        m_Deck.push_back(make_unique<DodgeCard>());

    // ================== EFFECT ==================
    for (int i = 0; i < 2; ++i)
        m_Deck.push_back(make_unique<RageIncreaseCard>());
    for (int i = 0; i < 2; ++i)
        m_Deck.push_back(make_unique<JackpotRollCard>());

    for (int i = 0; i < 2; ++i)
        m_Deck.push_back(make_unique<DoubleJackpotRollCard>());

    // ================== CHECK ===================
    if (m_Deck.size() != INITIAL_DECK_SIZE) {
        cout << format("[ERROR] Deck size sai! Hien tai = {}, can = {}", 
        m_Deck.size(), INITIAL_DECK_SIZE) << endl;
    }
}

/**
 * @brief Xáo trộn Deck bằng RNG chuẩn.
 */
void Deck::shuffle() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    // Tạo engine và shuffle
    std::default_random_engine engine(seed);

    // Sử dụng std::shuffle để xáo trộn
    std::shuffle(m_Deck.begin(), m_Deck.end(), engine);

    cout << "[DECK] Da xao tron bo bai." << endl;
}


/**
 * @brief Rút 1 lá bài ngẫu nhiên.
 */
unique_ptr<Card> Deck::drawCard() {
    if (m_Deck.empty()) {
        cout << "[DECK] Het bai!" << endl;
        return nullptr;
    }

    int index = rand() % m_Deck.size();
    unique_ptr<Card> card = move(m_Deck[index]);
    m_Deck.erase(m_Deck.begin() + index);

    cout << "[DECK] Rut duoc la bai: " << card->name << endl;
    return card;
}

/**
 * @brief Refill Deck nếu bài gần hết.
 */
void Deck::checkAndRefillDeck(int threshold) {
    if (m_Deck.size() <= threshold) {
        cout << "\n========== REFILL DECK ==========" << endl;
        cout << format("Deck con {} la bai. Dang bo sung...", m_Deck.size()) << endl;

        initializeFullDeck(); // bổ sung lại bộ bài
        shuffle(); // xáo trộn lại

        cout << "Deck da duoc refill day du!\n" << endl;
    }
}
