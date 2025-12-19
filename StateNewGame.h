#pragma once
#include "State.h"
#include "Player.h"
#include "Deck.h"
#include "Effect/EffectScheduler.h"
class BattleSystem;
#include <vector>
#include <memory>

class StateNewGame : public State {
private:
    std::unique_ptr<Player> m_player1;
    std::unique_ptr<Player> m_player2;
    std::unique_ptr<Deck>   m_deck;

    // 6 lá rút mỗi lượt
    std::vector<std::unique_ptr<Card>> m_hand;

    Player* m_current;
    Player* m_opponent;

    bool m_isGameOver = false;
    int  m_turnCount = 1;

    void swapTurns();			// đổi người chơi
    void drawHand();          // rút 6 lá
    void endTurn();
    void processEndOfTurn();  // xử lý độc, kiểm tra chết

public:
    // quản lí tấc cả hiệu ứng
    EffectScheduler scheduler;
    BattleSystem* battle;

    StateNewGame();
        
    ~StateNewGame() override = default;

    void Init() override;
    void Handle() override;
    void Render() override;

    void Exit() override;
    void Pause() override {}
    void Resume() override {}
};
