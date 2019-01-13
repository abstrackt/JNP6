#ifndef JNP6_HELPER_H
#define JNP6_HELPER_H

#include <algorithm>

typedef unsigned long AttackPower;
typedef unsigned long ShieldPoints;
typedef unsigned long Speed;

class Starship {
public:
    virtual ~Starship() = default;

    virtual ShieldPoints getShield() const = 0;

    virtual size_t getCount() const = 0;

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

    size_t getCount() const override {
        if(this->getShield() > 0) return 1;
        else return 0;
    }

    ShieldPoints getShield() const override {
        return this->shield;
    }

    void takeDamage(AttackPower damage) override {
        this->shield -= std::min(this->shield, damage);
    }
};

class SoloCombatStarship : virtual public CombatStarship {
private:
    const AttackPower power;
public:
    SoloCombatStarship(AttackPower power) : power(power) {};

    AttackPower getAttackPower() const override {
        return this->power;
    }
};

#endif //JNP6_HELPER_H
