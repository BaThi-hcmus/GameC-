#pragma once
#include "State.h"
#include "../GameObject/Player/Player.h"
#include "../GameObject/Deck/Deck.h"
#include "../GameObject/Effect/EffectScheduler.h"

#include <vector>
#include <memory>

class BattleSystem;

using namespace std;

class StateNewGame : public State {
private:
    // quản lí tấc cả hiệu ứng
    EffectScheduler _scheduler;
    BattleSystem* _battle;

    unique_ptr<Player> _player1;
    unique_ptr<Player> _player2;
    unique_ptr<Deck>   _deck;

    // 6 lá rút mỗi lượt
    vector<unique_ptr<Card>> _hand;

    Player* _current;
    Player* _opponent;

    bool _isGameOver = false;
    int  _turnCount = 1;

    void swapTurns();			// đổi người chơi
    void drawHand();          // rút 6 lá
    void endTurn();
    void processEndOfTurn();  // xử lý độc, kiểm tra chết
public:
    EffectScheduler& getScheduler();
    BattleSystem* getBattle();
public:
    StateNewGame();
        
    ~StateNewGame() override = default;

    void Init() override;
    void Handle() override;
    void Render() override;

    void Exit() override;
    void Pause() override {}
    void Resume() override {}
};
