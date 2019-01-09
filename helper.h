//
// Created by Andrzej on 07.01.2019.
//

#ifndef JNP6_HELPER_H
#define JNP6_HELPER_H

class AttackPower {
public:
    unsigned int power;
    AttackPower(unsigned int power);
};

class ShieldPoints {
public:
    unsigned int points;

    ShieldPoints(unsigned int points);

    void decreaseShield(AttackPower value);
};

class Speed {
public:
    unsigned int speed;

    Speed(unsigned int speed);
};

class Starship {
private:
    ShieldPoints shield;

protected:
    Starship(ShieldPoints shield);

public:
    virtual ~Starship() = default;

    ShieldPoints getShield();
    void takeDamage(AttackPower damage);
    virtual void attack(Starship &s);
};

class CombatStarship : public Starship {
private:
    AttackPower power;

protected:
    CombatStarship(ShieldPoints shield, AttackPower power);

public:
    AttackPower getAttackPower();
    void attack(Starship &s) override;
};

#endif //JNP6_HELPER_H
