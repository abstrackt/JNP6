#ifndef JNP6_HELPER_H
#define JNP6_HELPER_H

#include <algorithm>

class AttackPower {
private:
    unsigned int power;
public:
    AttackPower(unsigned int power) {
        this->power = power;
    }

    unsigned int getValue() {
        return power;
    }

    AttackPower operator+(const AttackPower& other) const {
        return AttackPower(this->power + other.power);
    }

    AttackPower &operator+=(const AttackPower& other) {
        this->power += other.power;
        return *this;
    }
};

class ShieldPoints {
private:
    unsigned int points;
public:
    ShieldPoints(unsigned int points) {
        this->points = points;
    }

    void decreaseShield(AttackPower value) {
        this->points -= std::min(value.getValue(), this->points);
    }

    unsigned int getValue() {
        return points;
    }

    ShieldPoints operator+(const ShieldPoints& other) const {
        return ShieldPoints(this->points + other.points);
    }

    ShieldPoints &operator+=(const ShieldPoints& other) {
        this->points += other.points;
        return *this;
    }
};

class Speed {
private:
    unsigned int speed;
public:
    Speed(unsigned int speed) {
        this->speed = speed;
    }

    unsigned int getValue() {
        return speed;
    }
};

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
        if(this->getShield().getValue() > 0) return 1;
        else return 0;
    }

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
