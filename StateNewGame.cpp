#include "StateNewGame.h"
#include "StateManager.h"
#include "GameConfig.h"

#include <iostream>

using namespace std;

StateNewGame::StateNewGame() {}

void StateNewGame::Init() {
    cout << "\n===== BAT DAU TRAN DAU=====" << endl;

	// Load cấu hình game
	GameConfig::instance().loadFromFile("game_config.txt");
	Player::loadConfig();

    m_player1 = make_unique<Player>();
    m_player2 = make_unique<Player>();
    m_deck    = make_unique<Deck>();

    m_current  = m_player1.get();
    m_opponent = m_player2.get();

    drawHand(); // rút 6 lá đầu tiên
}

// hàm rút 6 lá bài mỗi lượt
void StateNewGame::drawHand() {
    m_hand.clear();
    while (m_hand.size() < 6) {
        auto c = m_deck->drawCard(); //rút 1 lá ngẫu nhiên từ deck
        if (!c) {
            m_deck->checkAndRefillDeck();
            continue;
        }
        m_hand.push_back(move(c));
    }
}

void StateNewGame::swapTurns() {
    std::swap(m_current, m_opponent);
    m_turnCount++;
}

void StateNewGame::processEndOfTurn() {
    if (m_current->hp <= 0 || m_opponent->hp <= 0)
        m_isGameOver = true;
}

void StateNewGame::Handle() {
    if (m_isGameOver) {
        cout << "=======TRAN DAU KET THUC!==========" << endl;
        StateManager::getInstance()->ChangeState(0);
        return;
    }

    cout << "\n=== LUOT " << m_turnCount
         << " | HAKARI "
         << (m_current == m_player1.get() ? "P1" : "P2")
         << " ===" << endl;

	// ===== RESET TRANG THAI LUOT =====
    m_current->resetTurnState();

    //xử lí hiệu ứng choáng 
    if (m_current->hasEffect(EffectTag::Stun)) {
        cout << "[CHOANG] Ban bi mat luot!\n";

        // Hiệu ứng cuối lượt vẫn chạy nếu có (như đốt, độc,...)
        m_current->updateEffectsEndTurn();


        processEndOfTurn();
        if (m_isGameOver)
            return;

        swapTurns();
        drawHand();
        return;
    }

    //kích hoạt các hiệu ứng đầu lượt : jackpot
    for (auto& eff : m_current->effects) {
        eff->onTurnStart(*m_current);
    }

    //nếu ko có hiệu ứng jackpot thì mới cho phép chủ động phân bố chú lực
    if(!m_current->hasEffect(EffectTag::Jackpot)) {
        // ===== PHAN BO CHU LUC =====
        int atk, def, jp;
        cout << "\nPhan bo 5 diem chu luc (Tan cong / Phong thu / Jackpot): ";
        cin >> atk >> def >> jp;

        while (atk + def + jp != Player::MAX_CURSED_ENERGY) {
            cout << "Tong phai bang 5, nhap lai: ";
            cin >> atk >> def >> jp;
        }
        m_current->allocateCursedEnergy(atk, def, jp);
    }

    cout << " ===> Cac la bai trong tay:" << endl;
    for (int i = 0; i < m_hand.size(); ++i)
        cout << i + 1 << ". " << m_hand[i]->name << endl;

    cout << "Chon 4 la bai (nhap 4 so): ";

    vector<int> picks(4);
    for (int& x : picks) cin >> x;

    for (int idx : picks) {
        if (idx < 1 || idx > m_hand.size()) continue;
        m_hand[idx - 1]->execute(*m_current, *m_opponent);
    }

	// ===== CAP NHAT TRANG THAI CUOI LUOT =====
    m_current->updateEffectsEndTurn();

    processEndOfTurn();

    if (!m_isGameOver) {
        swapTurns();
        drawHand();
    }
}

void StateNewGame::Render() {
    cout << "\n--- TRANG THAI ---" << endl;
    cout << "P1 HP: " << m_player1->hp << " | P1 RAGE: " << m_player1->rage << " | P1 SHIELD: " << m_player1->shield << endl;
    cout << "P2 HP: " << m_player2->hp << " | P2 RAGE: " << m_player2->rage << " | P2 SHIELD: " << m_player2->shield << endl;
}

void StateNewGame::Exit() {
    cout << "Thoat khoi StateNewGame." << endl;
}
