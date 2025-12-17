// StatusEffect.h
#pragma once
class Player;

/**
 * @brief Lớp cha cho mọi hiệu ứng trạng thái trong game
 */
class StatusEffect {
protected:
    int duration; // số lượt còn lại

public:
    StatusEffect(int turns) : duration(turns) {}
    virtual ~StatusEffect() = default;

    // Các hook – effect nào cần thì override
    virtual void onApply(Player&) {}
    virtual void onTurnStart(Player&) {}
    virtual void onAfterReceiveDamage(Player&, int& damage) {}
    virtual void onTurnEnd(Player&) {}
    virtual void onRemove(Player&) {}

    // Giảm lượt, trả về true nếu hết hạn
    bool tick() { return --duration <= 0; }
};
