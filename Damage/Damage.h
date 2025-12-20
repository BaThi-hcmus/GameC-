#pragma once
class Player;

using namespace std;

class Damage {
protected:
    int _amount;
public:
    int getAmount();
    void setAmount(int amount);
public:
    virtual void apply(Player& target) = 0; // logic trừ HP, shield, etc.
    virtual ~Damage() {}
};
