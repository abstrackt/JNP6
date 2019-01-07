//
// Created by Andrzej on 07.01.2019.
//

#ifndef JNP6_HELPER_H
#define JNP6_HELPER_H

class AttackPower {
public:
    unsigned int power;
};

class ShieldPoints {
private:
    unsigned int points;
public:
    void decreaseShield(AttackPower value);
};

class Speed {
public:
    unsigned int speed;
};

class Starship {
private:
    ShieldPoints shield;

public:
    ShieldPoints getShield();
    void takeDamage(AttackPower damage);
    virtual void attack(Starship &s);
};

class CombatStarship : public Starship {
private:
    AttackPower power;

public:
    AttackPower getAttackPower();
    void attack(Starship &s) override;
};

#endif //JNP6_HELPER_H
