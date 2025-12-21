#include "StateNewGame.h"
#include "../GameManager/StateManager.h"
#include "../GameObject/NewGameConfig/GameConfig.h"
#include "../GameObject/BattleSystem/BattleSystem.h"

#include <format>
#include <iostream>

EffectScheduler& StateNewGame::getScheduler() {
    return _scheduler;
}

BattleSystem* StateNewGame::getBattle() {
    return _battle;
}

StateNewGame::StateNewGame() {
    _battle = new BattleSystem(_scheduler);
}

void StateNewGame::Init() {
    cout << "\n===== BAT DAU TRAN DAU=====" << endl;

	// Load cấu hình game
	GameConfig::instance().loadFromFile("GameObject/NewGameConfig/game_config.txt");
	Player::loadConfig();

    _player1 = make_unique<Player>();
    _player2 = make_unique<Player>();
    _deck    = make_unique<Deck>();

    _current  = _player1.get();
    _opponent = _player2.get();
}

// hàm rút 6 lá bài mỗi lượt
void StateNewGame::drawHand() {
    cout << "\n[DECK] rut 6 la tu bo bai : \n";

    _hand.clear();
    while (_hand.size() < 6) {
        auto c = _deck->drawCard(); //rút 1 lá ngẫu nhiên từ deck
        if (!c) {
            _deck->checkAndRefillDeck();
            continue;
        }
        _hand.push_back(move(c));
    }
}

void StateNewGame::swapTurns() {
    swap(_current, _opponent);
    _turnCount++;
}

void StateNewGame::endTurn() {
    _scheduler.tickPlayer(*_current);   // giảm duration, xóa effect hết hạn
    swapTurns();
}


void StateNewGame::processEndOfTurn() {
    if (_current->getHp() <= 0 || _opponent->getHp() <= 0)
        _isGameOver = true;
}

void StateNewGame::Handle() {
    if (_isGameOver) {
        cout << "=======TRAN DAU KET THUC!==========" << endl;
        StateManager::getInstance()->ChangeState(0);
        return;
    }

    cout << "\n=== LUOT " << _turnCount
         << " | HAKARI "
         << (_current == _player1.get() ? "P1" : "P2")
         << " ===" << endl;

	// ===== RESET TRANG THAI LUOT =====
    _current->resetTurnState();

    // xử lí choáng 
    if (_scheduler.hasEffect(_current, EffectTag::Stun)) {
        cout << "[CHOANG] Ban bi mat luot!\n\n";

        // Hiệu ứng cuối lượt vẫn chạy nếu có (như đốt, độc,...)
        _battle->onTurnEnd(*_current);

        processEndOfTurn();
        if (_isGameOver)
            return;

        endTurn();
        return;
    }

    drawHand();

    //kích hoạt các hiệu ứng đầu lượt : jackpot
    _battle->onTurnStart(*_current);

    //nếu ko có hiệu ứng jackpot thì mới cho phép chủ động phân bố chú lực
    if(!_scheduler.hasEffect(_current, EffectTag::Jackpot)) {
        // ===== PHAN BO CHU LUC =====
        int atk, def, jp;
        cout << "\nPhan bo 5 diem chu luc (Tan cong / Phong thu / Jackpot): ";
        cin >> atk >> def >> jp;

        while (atk + def + jp != Player::MAX_CURSED_ENERGY) {
            cout << "Tong phai bang 5, nhap lai: ";
            cin >> atk >> def >> jp;
        }
        _current->allocateCursedEnergy(atk, def, jp);
    }

    cout << "Phan bo chu luc hien tai : \n";
    cout << format("[ATTACK] : {} => buff them 10% damage gay ra cho moi diem chu luc\n", _current->getAttackEnergy());
    cout << format("[DEFENSE] : {} => giam di 10% damage nhan vao cho moi diem chu luc\n", _current->getDefenseEnergy());
    cout << format("[JACKPOT] : {} => tang 1 diem no II cho moi diem chu luc\n\n", _current->getJackpotEnergy());

    cout << " ===> Cac la bai trong tay:" << endl;
    for (int i = 0; i < _hand.size(); ++i)
        cout << i + 1 << ". " << _hand[i]->_name << endl;

    cout << "Chon 4 la bai (nhap 4 so): ";

    vector<int> picks(4);
    for (int& x : picks) cin >> x;

    cout << "=====================================\n\n";

    for (int idx : picks) {
        if (idx < 1 || idx > _hand.size()) continue;
        _hand[idx - 1]->execute(*_current, *_opponent, *this);
    }

    _battle->onTurnEnd(*_current);

    processEndOfTurn();

    if (!_isGameOver) {
        endTurn();
    }
}

void StateNewGame::Render() {
    cout << "\n--- TRANG THAI ---" << endl;
    cout << "P1 HP: " << _player1->getHp() << " | P1 RAGE: " << _player1->getRage() << " | P1 SHIELD: " << _player1->getShield() << endl;
    cout << "P2 HP: " << _player2->getHp() << " | P2 RAGE: " << _player2->getRage() << " | P2 SHIELD: " << _player2->getShield() << endl;
}

void StateNewGame::Exit() {
    cout << "Thoat khoi StateNewGame." << endl;
}


