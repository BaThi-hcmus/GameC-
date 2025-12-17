#include "Player.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

// Player.cpp
int Player::MAX_HP = 0;
int Player::MAX_RAGE = 0;
int Player::MAX_CURSED_ENERGY = 0;

// CONSTRUCTOR
Player::Player() {
    hp = MAX_HP;
    shield = 0;
    rage = 0; // nộ ii ban đầu

    attackEnergy = 0; // chú lực tấn công
    defenseEnergy = 0; // chú lực phòng thủ

    isStunned = false; // trạng thái choáng
    stunTurns = 0; // số lượt choáng

    hasDodge = false; // trạng thái né
    dodgeChance = 0.0f; // tỉ lệ né

    hasDamageReduction = false; // trạng thái giảm sát thương
    damageReductionRatio = 0.0f; // tỉ lệ giảm sát thương

    jackpotMode = false; // trạng thái jackpot
    jackpotTurns = 0; // số lượt jackpot
    jackpotBlocked = false; // trạng thái cấm jackpot
}

// LOAD CẤU HÌNH TỪ FILE
void Player::loadConfig() {
    auto& conf = GameConfig::instance();
    MAX_HP = conf.getInt("PLAYER_MAX_HP");
    MAX_RAGE = conf.getInt("PLAYER_MAX_RAGE");
    MAX_CURSED_ENERGY = conf.getInt("PLAYER_CURSED_ENERGY_PER_TURN");
}

// RESET TRẠNG THÁI MỖI LƯỢT
void Player::resetTurnState() {
    attackEnergy = 0;
    defenseEnergy = 0;
    hasDodge = false; // reset né
    hasDamageReduction = false; // reset giảm sát thương
    dodgeChance = 0.0f; // reset tỉ lệ né
    damageReductionRatio = 0.0f; // reset tỉ lệ giảm sát thương
}

// CẬP NHẬT TRẠNG THÁI SAU MỖI LƯỢT
void Player::updateStatus() {
    // Xử lý choáng
    if (isStunned) {
        stunTurns--;
        if (stunTurns <= 0) {
            isStunned = false;
            cout << "\nBan da het hieu ung bi choang\n";
        }
    }

    // Xử lý Jackpot
    if (jackpotMode) {
        jackpotTurns--;
        hp = MAX_HP; // hồi đầy máu mỗi lượt

        // dồn hết 5 điểm chú lực cho tấn công
        attackEnergy = MAX_CURSED_ENERGY;
        defenseEnergy = 0;

        cout << "[JACKPOT MODE]: Ban duoc hoi day HP va full chu luc tan cong!\n";

        if (jackpotTurns <= 0) {
            jackpotMode = false;
            cout << "[JACKPOT MODE]: Ban da het Jackpot Mode.\n";
        }
    }

    // xử lý khóa Jackpot
    if (jackpotCooldownTurns > 0) {
        jackpotCooldownTurns--;

        if (jackpotCooldownTurns == 0) {
            jackpotBlocked = false;
            cout << "[JACKPOT]: Ban da co the quay Jackpot lai.\n";
        }
    }
}


void Player::allocateCursedEnergy(int atk, int def, int jackpot) {
    int total = atk + def + jackpot;
    if (total != MAX_CURSED_ENERGY) {
        cout << "Tong chu luc phai bang 5!\n";
        return;
    }

    attackEnergy = atk;
    defenseEnergy = def;
    jackpotEnergy = jackpot;

    // mỗi điểm jackpot tăng 1 rage
    if (jackpotEnergy > 0) {
        increaseRage(jackpotEnergy);
    }

    cout << "[PHAN BO CHU LUC]\n";
    cout << "- Tan cong: " << attackEnergy << endl;
    cout << "- Phong thu: " << defenseEnergy << endl;
    cout << "- Jackpot: " << jackpotEnergy << endl;
}


// NHẬN TẤN CÔNG THƯỜNG
void Player::receiveAttack(int baseDamage, Player& attacker) {
    cout << "Tan cong thuong: " << baseDamage <<" damage" << endl;

    // Nhân damage theo chú lực tấn công
    float scaleAttack = GameConfig::instance().getFloat("ATTACK_ENERGY_DAMAGE_SCALE");
    float multiplier = 1.0f + attacker.attackEnergy * scaleAttack;
    int finalDamage = static_cast<int>(baseDamage * multiplier);


    // tính chí mạng: nếu có phân bố chú lực tấn công thì tăng 15% chí mạng
    if(attacker.attackEnergy > 0) {
        int critRoll = rand() % 100;
        float chance = GameConfig::instance().getFloat("CRIT_CHANCE");
        int multiplierCrit = GameConfig::instance().getInt("CRIT_DAMAGE_MULTIPLIER");

        if (critRoll < chance) {
            finalDamage = static_cast<int>(finalDamage * multiplierCrit); // chí mạng gấp 3 sát thương
            cout << "CHÍ MẠNG! Sat thuong tang len: " << finalDamage << endl;
        }
    }

    // Giảm sát thương theo lượng chú lực phòng thủ
    float scaleDefense = GameConfig::instance().getFloat("DEFENSE_ENERGY_DAMAGE_REDUCTION_SCALE");
    int damageReduction = defenseEnergy * scaleDefense * baseDamage; // mỗi điểm chú lực phòng thủ giảm 10% sát thương
    finalDamage -= damageReduction;
    if (finalDamage < 0) finalDamage = 0;

    // Né đòn
    if (hasDodge && (rand() % 100) < dodgeChance * 100) {
        cout << "Doi thu ne don thanh cong\n";
        return;
    }

    if (hasDamageReduction) {
        finalDamage *= (1.0f - damageReductionRatio);
        cout << "Doi thu da giam " << damageReductionRatio * 100 << "% sat thuong nhan vao.\n";
    }

    // Trừ giáp trước
    int absorbed = min(shield, finalDamage);
    shield -= absorbed;
    finalDamage -= absorbed;

    // Trừ HP
    hp -= finalDamage;
    if (hp < 0) hp = 0;

    cout << ">> Sat thuong thuc te: " << finalDamage << endl;
}

// TẤN CÔNG XUYÊN GIÁP
void Player::receivePierceAttack(int baseDamage, Player& attacker) {
    cout << "Tan cong xuyen giap: " << baseDamage <<" damage" << endl;
    
    // Không cần giảm sát thương, xuyên giáp
    float scaleAttack = GameConfig::instance().getFloat("ATTACK_ENERGY_DAMAGE_SCALE");
    float multiplier = 1.0f + attacker.attackEnergy * scaleAttack;
    int finalDamage = static_cast<int>(baseDamage * multiplier);

    // Giảm sát thương theo lượng chú lực phòng thủ
    float scaleDefense = GameConfig::instance().getFloat("DEFENSE_ENERGY_DAMAGE_REDUCTION_SCALE");
    int damageReduction = defenseEnergy * scaleDefense * baseDamage; // mỗi điểm chú lực phòng thủ giảm 10% sát thương
    finalDamage -= damageReduction;
    if (finalDamage < 0) finalDamage = 0;

    //trừ thẳng vào HP
    hp -= finalDamage;
    if (hp < 0) hp = 0;

    cout << ">> HP cua doi thu bi tru truc tiep: " << finalDamage
         << " | HP con lai: " << hp << endl;
}

// PHÒNG THỦ
void Player::addShield(int amount) {
    shield += amount;
    cout << "Shield tang them: " << amount
         << " | Shield hien tai: " << shield << endl;
}

void Player::activateDamageReduction(float ratio) {
    hasDamageReduction = true;
    damageReductionRatio = ratio;
    cout << "Ban co the giam " << ratio * 100 << "% sat thuong nhan vao.\n";
}

void Player::activateDodge(float chance) {
    hasDodge = true;
    dodgeChance = chance;
    cout << "Ban co the ne don voi ti le : " << chance * 100 << "%\n";
}

// HIỆU ỨNG KHÁC
void Player::applyStun(int turns) {
    isStunned = true;
    stunTurns = turns;
    cout << "Doi thu se bi choang trong " << turns << " luot!\n";
}

void Player::increaseRage(int amount) {
    rage = min(MAX_RAGE, rage + amount);
    cout << "No ii cua ban tang them: " << amount
         << " | Nộ ii hien tai: " << rage << endl;
}

// JACKPOT
void Player::rollJackpot(int times, Player& target) {
    if (jackpotBlocked) {
        cout << "!! Ban dang bi cam quay Jackpot!\n";
        return;
    }

    for (int i = 0; i < times; i++) {
        //tỉ lệ trúng jackpot cơ bản là 1/12 : làm trong xuống 8
        int defaultChance = GameConfig::instance().getInt("JACKPOT_CHANCE");
        int chance = defaultChance + rage * 2;
        int roll = rand() % 100;

        cout << ">> Quay Jackpot (" << chance << "%)... ";

        if (roll < chance) {
            cout << "BAN DA TRUNG DOC DAC!!!\n";
            rage = 0;
            activateJackpot(target);
            return;
        }
        cout << "That bai.\n";
    }
}

void Player::activateJackpot(Player& target) {
    jackpotMode = true;
    jackpotTurns = GameConfig::instance().getInt("JACKPOT_DURATION_TURNS");
    jackpotBlocked = true; //trong 5 lượt duy trì jackpot + 1 lượt tiếp theo sẽ không thể quay lại
    jackpotCooldownTurns = GameConfig::instance().getInt("JACKPOT_BLOCK_TURNS"); //số lượt bị khóa quay jackpot

    //áp dụng hiệu ứng choáng 1 lượt lên đối thủ khi quay trúng jackpot
    target.applyStun(1);

    cout << "JACKPOT MODE : ban da quay ra Jackpot!\n";
    cout << ">> Hieu ung nhan duoc :\n-- hoi day thanh HP\n-- full chu luc tan cong trong 5 luot\n-- gay choang doi thu trong luot ke tiep\n\n";
}
