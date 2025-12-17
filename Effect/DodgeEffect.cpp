// DodgeEffect.cpp
#include "DodgeEffect.h"
#include "Player.h"
#include <iostream>

void DodgeEffect::onApply(Player& p) {
    p.hasDodge = true;
    p.dodgeChance = chance;
}

void DodgeEffect::onRemove(Player& p) {
    p.hasDodge = false;
    p.dodgeChance = 0.0f;
}
