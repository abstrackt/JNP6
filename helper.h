#ifndef JNP6_HELPER_H
#define JNP6_HELPER_H

#include "parameters.h"

class Starship {
public:
    virtual ~Starship() = default;

    virtual ShieldPoints getShield() const = 0;

    virtual void takeDamage(AttackPower damage) = 0;
};

class CombatStarship : virtual public Starship {
public:
    virtual AttackPower getAttackPower() const = 0;
};

class SoloStarship : virtual public Starship {
private:
    ShieldPoints shield;
public:
    SoloStarship(ShieldPoints shield) : shield(shield) {}

    ShieldPoints getShield() const override {
        return this->shield;
    }

    void takeDamage(AttackPower damage) override {
        this->shield.decreaseShield(damage);
    }
};

class SoloCombatStarship : virtual public CombatStarship {
private:
    AttackPower power;
public:
    SoloCombatStarship(AttackPower power) : power(power) {};

    AttackPower getAttackPower() const override {
        return this->power;
    }
};

#endif //JNP6_HELPER_H
