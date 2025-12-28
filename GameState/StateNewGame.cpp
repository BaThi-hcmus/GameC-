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

void StateNewGame::selectGameMode() {
    int mode = 0;
    cout << "Chon che do choi:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs BOT\n";
    cout << "Nhap lua chon cua ban ==> ";
    cin >> mode;

    while(mode < 1 || mode > 2) {
        cout << "Nhap lai : ";
        cin >> mode;
    }
    
    switch(mode) {
        case 1 : 
            // P1 vs P2 (cả hai là người chơi)
            _player1 = make_unique<Player>();
            _player2 = make_unique<Player>();
            break;
        case 2 : {
            // P1 là người, P2 là BOT
            _player1 = make_unique<Player>();

            cout << "\nChon doi thu:\n";
            cout << "1. Hakari (May)\n";
            cout << "2. Charles Bernard (De)\n";
            cout << "3. Kashimo Hajime (TB)\n";
            cout << "4. Uraume (Kho)\n";
            cout << "Nhap lua chon cua ban ==> ";

            int botChoice = 0;
            cin >> botChoice;

            while(botChoice < 1 || botChoice > 5) {
                cout << "Nhap lai : ";
                cin >> botChoice;
            }

            switch (botChoice) {
                case 1: _player2 = make_unique<BotHakari>(); break;
                case 2: _player2 = make_unique<CharlesBoss>(); break;
                case 3: _player2 = make_unique<KashimoBoss>(); break;
                case 4: _player2 = make_unique<UraumeBoss>(); break;
                default:
                    cout << "Lua chon khong hop le, mac dinh Hakari.\n";
                    _player2 = make_unique<BotHakari>();
                    break;
            }
            break;
        }
        default :
            cout << "Lua chon khong hop le, mac dinh Player vs Player.\n";
            _player1 = make_unique<Player>();
            _player2 = make_unique<Player>();
    }
}


void StateNewGame::Init() {
    GameConfig::instance().loadFromFile("GameObject/NewGameConfig/game_config.txt");
	Player::loadConfig();
    selectGameMode();

    if (_player2->isBot())
        cout << "\n[THONG TIN BOSS]: \n" << dynamic_cast<BotPlayer*>(_player2.get())->getInfo() << endl;

    cout << "\n===== BAT DAU TRAN DAU=====" << endl;

    _deck    = make_unique<Deck>();
  
    _current  = _player1.get();
    _opponent = _player2.get();
}

// hàm rút 6 lá bài mỗi lượt
void StateNewGame::drawHand() {
    cout << "\n[DECK] rut 6 la tu bo bai : \n";

    //reset bên deck
    _deck->startNewHand();
    _hand.clear();
    while (_hand.size() < 6) {
        auto c = _deck->drawCard(); //rút 1 lá ngẫu nhiên từ deck
        if (!c) continue;
        
        _hand.push_back(move(c));
    }
}

void StateNewGame::swapTurns() {
    swap(_current, _opponent);
    _turnCount++;
}

void StateNewGame::endTurn() {
    _scheduler.tickByTrigger(TickTrigger::endOfTurn, *_current);   // giảm duration, xóa effect hết hạn
    _scheduler.tickByTrigger(TickTrigger::endOfTurnOpponent, *_opponent); //giảm các hiệu ứng của đối thủ trong lượt này
    // ví dụ : giảm sát thương, né đòn,...
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

    cout << "\n=== LUOT " << _turnCount << " | ";
    if (!_current->isBot() && !_opponent->isBot()) {
        if (_current == _player1.get()) cout << "PLAYER 1 ===\n";
        else cout <<"PLAYER 2 ===\n";
    } else {
        if (auto bot = dynamic_cast<BotPlayer*>(_current)) {
            cout << bot->getName() << " ===\n";
        } else cout << "LUOT CUA BAN ===\n";
    }
	// ===== RESET TRANG THAI LUOT =====
    _current->resetTurnState();

    if (auto bot = dynamic_cast<BotPlayer*>(_current)) {
        bot->onTurnStart();  // BOT : đếm số lượt
        bot->applyPassiveIfActive(_scheduler); // CharlesBoss => kích hoạt hiệu ứng né đòn (nếu có)
        if (bot->hasSpecialSkillReady()) { // KashimoBoss => Gây 400 damage xuyên giáp
            bot->executeSpecialSkill(*_opponent, *_battle);
        }
        bot->onOpponentAllocatedEnergy(*_opponent, _scheduler); // UraumeBoss => Kích hoạt đây choáng đối thủ trong lượt kế
    }


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
        _current->allocateCursedEnergy();
    }

    cout << "Phan bo chu luc hien tai : \n";
    cout << format("[ATTACK] : {} => buff them 10% damage gay ra cho moi diem chu luc\n", _current->getAttackEnergy());
    cout << format("[DEFENSE] : {} => giam di 10% damage nhan vao cho moi diem chu luc\n", _current->getDefenseEnergy());
    cout << format("[JACKPOT] : {} => tang 1 diem no II cho moi diem chu luc\n\n", _current->getJackpotEnergy());

    cout << " ===> Cac la bai trong tay:" << endl;
    for (int i = 0; i < _hand.size(); ++i)
        cout << i + 1 << ". " << _hand[i]->_name << endl;

    // gọi hàm chọn bài 
    auto cardSelected = _current->pickCards(_hand);

    //thực thi các lá bài 
    for (auto c : cardSelected) {
        c->execute(*_current, *_opponent, *this);
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


