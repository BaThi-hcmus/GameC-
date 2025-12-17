// DamageReductionEffect.cpp
#include "DamageReductionEffect.h"
#include "Player.h"
#include <iostream>

void DamageReductionEffect::onAfterReceiveDamage(Player&, int& damage) {
    damage = static_cast<int>(damage * (1.0f - ratio));
}
