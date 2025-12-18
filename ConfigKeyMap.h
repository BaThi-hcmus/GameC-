// ConfigKeyMap.h
#pragma once
#include <unordered_map>
#include <string>
#include "ConfigKey.h"

inline const std::unordered_map<ConfigKey, std::string> ConfigKeyToString = {
    { ConfigKey::CARD_DAMAGE_NORMAL, "CARD_DAMAGE_NORMAL" },
    { ConfigKey::CARD_DAMAGE_PIERCE, "CARD_DAMAGE_PIERCE" },
    { ConfigKey::CARD_DAMAGE_STUN, "CARD_DAMAGE_STUN" },
    { ConfigKey::CARD_SHIELD_GAIN, "CARD_SHIELD_GAIN" },
    { ConfigKey::CARD_DAMAGE_REDUCTION_RATIO, "CARD_DAMAGE_REDUCTION_RATIO" },
    { ConfigKey::CARD_DODGE_CHANCE, "CARD_DODGE_CHANCE" },
    { ConfigKey::CARD_RAGE_GAIN, "CARD_RAGE_GAIN" },

    { ConfigKey::DECK_INITIAL_SIZE, "DECK_INITIAL_SIZE" },
    { ConfigKey::DECK_MIN_SIZE, "DECK_MIN_SIZE" },

    { ConfigKey::PLAYER_MAX_HP, "PLAYER_MAX_HP" },
    { ConfigKey::PLAYER_MAX_RAGE, "PLAYER_MAX_RAGE" },
    { ConfigKey::PLAYER_CURSED_ENERGY_PER_TURN, "PLAYER_CURSED_ENERGY_PER_TURN" },

    { ConfigKey::ATTACK_ENERGY_DAMAGE_SCALE, "ATTACK_ENERGY_DAMAGE_SCALE" },
    { ConfigKey::DEFENSE_ENERGY_DAMAGE_REDUCTION_SCALE, "DEFENSE_ENERGY_DAMAGE_REDUCTION_SCALE" },

    { ConfigKey::CRIT_CHANCE, "CRIT_CHANCE" },
    { ConfigKey::CRIT_DAMAGE_MULTIPLIER, "CRIT_DAMAGE_MULTIPLIER" },

    { ConfigKey::JACKPOT_CHANCE, "JACKPOT_CHANCE" },
    { ConfigKey::JACKPOT_DURATION_TURNS, "JACKPOT_DURATION_TURNS" },
    { ConfigKey::JACKPOT_BLOCK_TURNS, "JACKPOT_BLOCK_TURNS" }
};
