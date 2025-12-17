// StunEffect.cpp
#include "StunEffect.h"
#include "Player.h"

void StunEffect::onApply(Player& p) {
    p.isStunned = true;
    std::cout << ">> Doi thu bi choang!\n";
}

void StunEffect::onRemove(Player& p) {
    p.isStunned = false;
    std::cout << ">> Het choang.\n";
}
