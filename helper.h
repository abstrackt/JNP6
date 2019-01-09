#ifndef JNP6_HELPER_H
#define JNP6_HELPER_H

#include "rebelfleet.h"
#include "imperialfleet.h"

class AttackPower {
private:
    unsigned int power;
public:
    AttackPower(unsigned int power) {
        this->power = power;
    }

    unsigned int getValue(){
        return power;
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
    };

    unsigned int getValue(){
        return points;
    }
};

class Speed {
private:
    unsigned int speed;
public:
    Speed(unsigned int speed) {
        this->speed = speed;
    }

    unsigned int getValue(){
        return speed;
    }
};

//INTERFACE
class Starship {
public:

    virtual ShieldPoints getShield() {};

    virtual void takeDamage(AttackPower damage) {};
};

//INTERFACE
class CombatStarship : public Starship {
public:
    virtual AttackPower getAttackPower() {};
};

class SoloStarship : public Starship {
private:
    ShieldPoints shield;
public:
    SoloStarship(ShieldPoints shield) {
        this->shield = shield;
    };

    ShieldPoints getShield() override {
        return this->shield;
    };

    void takeDamage(AttackPower damage) override {
        this->shield.decreaseShield(damage);
    };
};

class SoloCombatStarship : public CombatStarship {
private:
    AttackPower power;
public:
    SoloCombatStarship(AttackPower power) {
        this->power = power;
    };

    AttackPower getAttackPower() override {
        return this->power;
    };
};

class SoloImperialStarship : public virtual SoloCombatStarship,
                             public virtual ImperialStarship,
                             public virtual SoloStarship {
public:
    SoloImperialStarship(ShieldPoints shield, AttackPower power) : SoloStarship(shield),
                                                                   SoloCombatStarship(power) {};
};

class RebelCombatStarship : public virtual SoloCombatStarship,
                            public virtual RebelStarship {
public:
    RebelCombatStarship(ShieldPoints shield, AttackPower power, Speed speed) : RebelStarship(shield, speed),
                                                                               SoloCombatStarship(power) {};
    void engageTarget(ImperialStarship &s) override {
        this->takeDamage(s.getAttackPower());
        s.takeDamage(this->getAttackPower());
    };
};

#endif //JNP6_HELPER_H
