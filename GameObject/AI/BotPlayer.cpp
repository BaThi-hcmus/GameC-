#include "BotPlayer.h"

BotPlayer::BotPlayer(std::string name)
    : Player(), _botName(name), _turnCounter(0) {}

BotPlayer::~BotPlayer() {}

std::string BotPlayer::getName() const {
    return _botName;
}

bool BotPlayer::isBot() const {
    return true;
}

void BotPlayer::onTurnStart() {
    _turnCounter++;
}

std::vector<Card*> BotPlayer::pickCards(const std::vector<std::unique_ptr<Card>>& hand) {
    std::vector<Card*> selected;
    if (hand.size() >= 4) {
        for (int i = 0; i < 4; ++i)
            selected.push_back(hand[i].get());
    }
    return selected;
}

bool BotPlayer::hasSpecialSkillReady() { return false; }
void BotPlayer::executeSpecialSkill(Player&, BattleSystem&) {}
void BotPlayer::onOpponentAllocatedEnergy(Player&, EffectScheduler&) {}
void BotPlayer::applyPassiveIfActive(EffectScheduler&) {}
string BotPlayer::getInfo()  {
    return "";
}
