#ifndef JNP6_HELPER_H
#define JNP6_HELPER_H

#include <algorithm>

using AttackPower = unsigned long long;
using ShieldPoints = unsigned long long;
using Speed = unsigned long long;

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
        return this->getShield() > 0 ? 1 : 0;
    }

    ShieldPoints getShield() const override {
        return this->shield;
    }

    void takeDamage(AttackPower damage) override {
        auto damageTaken = std::min(this->shield, damage);
        this->shield -= damageTaken;
    }
};

class SoloCombatStarship : virtual public CombatStarship {
private:
    const AttackPower power;
public:
    SoloCombatStarship(AttackPower power) : power(power) {}

    AttackPower getAttackPower() const override {
        return this->power;
    }
};

#endif //JNP6_HELPER_H