#pragma once
#include <iostream>
#include <format>
#include "GameConfig.h"

/**
 * @brief Lớp Player đại diện cho một nhân vật trong game Hakari Card Battle.
 * Quản lý toàn bộ chỉ số, trạng thái và logic chiến đấu.
 */
class Player {
public:
    // HẰNG SỐ 
    static int MAX_HP;          // Máu tối đa
    static int MAX_RAGE;          // Nộ ii tối đa
    static int MAX_CURSED_ENERGY;  // Chú lực mỗi lượt
public:
    int hp;        // Máu hiện tại
    int shield;    // Giáp hiện tại
    int rage;      // Thanh nộ ii hiện tại

    // PHÂN BỐ CHÚ LỰC
    int attackEnergy;     // Chú lực dành cho tấn công
    int defenseEnergy;    // Chú lực dành cho phòng thủ
    int jackpotEnergy;   // Chú lực dành cho việc tăng tỉ lệ Jackpot

    // TRẠNG THÁI HIỆU ỨNG
    bool isStunned;       // Có đang bị choáng không
    int stunTurns;        // Số lượt choáng còn lại

    bool hasDodge;        // Có hiệu ứng né không
    float dodgeChance;    // Tỉ lệ né (0.0 → 1.0)

    bool hasDamageReduction;   // Có giảm sát thương không
    float damageReductionRatio;// Tỉ lệ giảm sát thương

    // TRẠNG THÁI JACKPOT
    bool jackpotMode;     // Đang ở chế độ Jackpot
    int jackpotTurns;     // Số lượt Jackpot còn lại
    bool jackpotBlocked;  // Có bị cấm quay Jackpot không
    int jackpotCooldownTurns; // Số lượt còn lại bị khóa quay Jackpot

    // CONSTRUCTOR
    Player();

    // CẤU HÌNH TỪ FILE
    static void loadConfig();

    // QUẢN LÝ LƯỢT
    void resetTurnState();    // Reset hiệu ứng theo lượt
    void updateStatus();      // Cập nhật trạng thái sau mỗi lượt

    // PHÂN BỐ CHÚ LỰC
    void allocateCursedEnergy(int atk, int def, int jackpot) ;

    // XỬ LÝ TẤN CÔNG
    void receiveAttack(int baseDamage, Player& attacker); // Nhận tấn công thường
    void receivePierceAttack(int baseDamage, Player& attacker); // Nhận tấn công xuyên giáp

    // PHÒNG THỦ
    void addShield(int amount); // Thêm shield
    void activateDamageReduction(float ratio); // Kích hoạt giảm sát thương
    void activateDodge(float chance); // Kích hoạt né tránh

    // HIỆU ỨNG KHÁC
    void applyStun(int turns); // Áp dụng choáng
    void increaseRage(int amount); // Tăng nộ ii

    // JACKPOT
    void rollJackpot(int times, Player& target); // Quay Jackpot
    void activateJackpot(Player& target); // Kích hoạt chế độ Jackpot
};
