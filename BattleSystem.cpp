#include "BattleSystem.h"
#include "Effect/JackpotEffect.h"
#include "Effect/StunEffect.h"
#include "Effect/CriticalStrikeEffect.h"

int BattleSystem::computeAttackDamage(Player& attacker, int baseDamage) {
    float atkScale = GameConfig::instance()
        .getFloat(ConfigKey::ATTACK_ENERGY_DAMAGE_SCALE);

    //kích hoạt hiệu ứng sát thương chí mạng nếu attacker có phân bố chú lực cho attack
    if(attacker.attackEnergy > 0) {
        float chance = GameConfig::instance().getFloat(ConfigKey::CRIT_CHANCE);
        int multiplier = GameConfig::instance().getInt(ConfigKey::CRIT_DAMAGE_MULTIPLIER);

        scheduler.addEffect(
            &attacker,
            std::make_unique<CriticalStrikeEffect>(1, chance, multiplier),
            TriggerType::onBeforeDealDamage,
            1
        );
    }

    return static_cast<int>(
        baseDamage * (1.0f + attacker.attackEnergy * atkScale)
    );
}

void BattleSystem::attack(Player& attacker, Player& defender, Damage& damage) {
    int baseDamage = damage.amount;

    //scale damage của attacker
    damage.amount = computeAttackDamage(attacker, damage.amount);

    // BEFORE DEAL
    scheduler.processTrigger(TriggerType::onBeforeDealDamage, attacker, &damage);

    // BEFORE RECEIVE
    scheduler.processTrigger(TriggerType::onBeforeReceiveDamage, defender, &damage);

    // defense energy
    float defScale = GameConfig::instance()
        .getFloat(ConfigKey::DEFENSE_ENERGY_DAMAGE_REDUCTION_SCALE);

    damage.amount -= static_cast<int>(defender.defenseEnergy * defScale * baseDamage);
    damage.amount = std::max(0, damage.amount);

    if (damage.amount == 0) {
        return;
    }

    // AFTER RECEIVE
    scheduler.processTrigger(TriggerType::onAfterReceiveDamage, defender, &damage);

    damage.apply(defender);
    //defender.applyDamage(damage);

    std::cout << ">> Damage cuoi: " << damage.amount
              << " | HP doi thu con lai: " << defender.hp << "\n";
}

void BattleSystem::rollJackpot(Player& roller, Player& target, int times) {
    // nếu đang có jackpot thì không cho quay
    if (scheduler.hasEffect(&roller, EffectTag::Jackpot)) {
        cout << "Ban chua the quay jackpot!\n";
        return;
    }

    for (int i = 0; i < times; ++i) {
        int baseChance = GameConfig::instance().getInt(ConfigKey::JACKPOT_CHANCE);

        int chance = baseChance + roller.rage * 2;
        int roll = rand() % 100;

        cout << "Quay Jackpot (" << chance << "%)... ";

        if (roll < chance) {
            cout << "TRUNG!!!\n";
            roller.rage = 0;
            activateJackpot(roller, target);
            return;
        }
        cout << "THAT BAI\n";
    }
}

void BattleSystem::activateJackpot(Player& roller, Player& target) {
    int buffTurns =
        GameConfig::instance().getInt(ConfigKey::JACKPOT_DURATION_TURNS);

    // buff cho bản thân
    auto jackpot = std::make_unique<JackpotEffect>(buffTurns);
    scheduler.addEffect(
        &roller,
        std::move(jackpot),
        TriggerType::onTurnStart,
        buffTurns
    );

    // choáng đối thủ
    scheduler.addEffect(
        &target,
        std::make_unique<StunEffect>(1),
        TriggerType::onTurnStart,
        1
    );

    cout << "[JACKPOT] Kich hoat!\n";
    cout << "Ban duoc nap full HP va auto attack energe vao dau moi luot + gay choang doi thu trong luot ke tiep\n";
}
