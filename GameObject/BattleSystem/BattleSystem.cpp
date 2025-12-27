#include "../BattleSystem/BattleSystem.h"
#include "../Effect/JackpotEffect.h"
#include "../Effect/StunEffect.h"
#include "../Effect/CriticalStrikeEffect.h"

int BattleSystem::computeAttackDamage(Player& attacker, int baseDamage) {
    float atkScale = GameConfig::instance()
        .getFloat(ConfigKey::ATTACK_ENERGY_DAMAGE_SCALE);

    //kích hoạt hiệu ứng sát thương chí mạng nếu attacker có phân bố chú lực cho attack
    if(attacker.getAttackEnergy() > 0) {
        float chance = GameConfig::instance().getFloat(ConfigKey::CRIT_CHANCE);
        int multiplier = GameConfig::instance().getInt(ConfigKey::CRIT_DAMAGE_MULTIPLIER);

        _scheduler.addEffect(
            &attacker,
            make_unique<CriticalStrikeEffect>(1, chance, multiplier, TickTrigger::endOfTurn),
            TriggerType::onBeforeDealDamage,
            1
        );
    }

    int damageAfterScale = static_cast<int>(
        baseDamage * (1.0f + attacker.getAttackEnergy() * atkScale)
    );
    cout << "[ATTACKER] buff "<< attacker.getAttackEnergy() * atkScale * 100 <<" % damage\n";
    return damageAfterScale;
}

void BattleSystem::attack(Player& attacker, Player& defender, Damage& damage) {
    int baseDamage = damage.getAmount();

    //scale damage của attacker
    damage.setAmount(computeAttackDamage(attacker, damage.getAmount()));

    // BEFORE DEAL
    _scheduler.processTrigger(TriggerType::onBeforeDealDamage, attacker, &damage);

    // BEFORE RECEIVE (ví dụ hiệu ứng dodge)
    _scheduler.processTrigger(TriggerType::onBeforeReceiveDamage, defender, &damage);

    // defense energy
    float defScale = GameConfig::instance()
        .getFloat(ConfigKey::DEFENSE_ENERGY_DAMAGE_REDUCTION_SCALE);
    cout << "[DEFENDER] giam " << defender.getDefenseEnergy() * defScale * 100 << " % damage\n";

    damage.setAmount(damage.getAmount() - static_cast<int>(defender.getDefenseEnergy() * defScale * baseDamage));
    damage.setAmount(max(0, damage.getAmount()));
    
    // đối phương né đòn thành công 
    if (damage.getAmount() == 0) {
        return;
    }

    // AFTER RECEIVE
    _scheduler.processTrigger(TriggerType::onAfterReceiveDamage, defender, &damage);

    damage.apply(defender);

    cout << ">> Damage cuoi: " << damage.getAmount()
              << " | HP doi thu con lai: " << defender.getHp() << "\n";
}

void BattleSystem::rollJackpot(Player& roller, Player& target, int times) {
    // không cho roolJackpot trong 5 lượt tác dụng + 1 lượt kế tiếp
    if (_scheduler.hasEffect(&roller, EffectTag::Jackpot)) {
        cout << "Ban chua the quay jackpot!\n";
        return;
    }

    for (int i = 0; i < times; ++i) {
        int baseChance = GameConfig::instance().getInt(ConfigKey::JACKPOT_CHANCE);

        int chance = baseChance + roller.getRage() * 2;
        int roll = rand() % 100;

        cout << "Quay Jackpot (" << chance << "%)... ";

        if (roll < chance) {
            cout << "TRUNG!!!\n";
            roller.setRage(0);
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
    auto jackpot = make_unique<JackpotEffect>(buffTurns, TickTrigger::endOfTurn);

    //kích hoạt hiệu ứng jackpot ngay trong lượt hiện tại
    jackpot->onApply(roller);
    _scheduler.addEffect(
        &roller,
        move(jackpot),
        TriggerType::onTurnStart,
        buffTurns
    );

    // choáng đối thủ
    _scheduler.addEffect(
        &target,
        make_unique<StunEffect>(1, TickTrigger::endOfTurn),
        TriggerType::onTurnStart,
        1
    );

    cout << "[JACKPOT] Kich hoat!\n";
    cout << "Ban duoc nap full HP va auto attack energe vao dau moi luot + gay choang doi thu trong luot ke tiep\n";
}
