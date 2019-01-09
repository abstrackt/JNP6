//
// Created by Andrzej on 09.01.2019.
//

#ifndef JNP6_PARAMETERS_H
#define JNP6_PARAMETERS_H

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

#endif //JNP6_PARAMETERS_H
