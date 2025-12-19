#pragma once
class Player;

class Damage {
public:
    int amount;
    virtual void apply(Player& target) = 0; // logic trừ HP, shield, etc.
    virtual ~Damage() {}
};
