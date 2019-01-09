#ifndef JNP6_BATTLE_H
#define JNP6_BATTLE_H

#include <cstdio>
#include <vector>
#include "imperialfleet.h"
#include "rebelfleet.h"

class Time {
private:
    unsigned int value;

public:
    virtual unsigned int getTime() {
        return this->value;
    };

    virtual void setTime(unsigned int steps) {
        this->value += steps;
    };

    virtual bool isAttackTime() {
        return this->value % 2 == 0 &&
               this->value % 3 == 0 &&
               this->value % 5 != 0;
    };
};

class SpaceBattle {
private:
    //tutaj na poziomie buildera możemy mieć dwie funkcje ship przyjmujące rebel/imperuial
    //ship, dzięki dwóm wektorom będziemy mogli łatwo przeprowadzać ataki w tick()
    std::vector<ImperialStarship> imperialForce;
    std::vector<RebelStarship> rebelForce;
    size_t imperialCount, rebelCount;
    Time t0, t1, tcurr;

    //TODO
    void conductAttack() {};

public:
    size_t countImperialFleet() {
        return this->imperialCount;
    };

    size_t countRebelFleet() {
        return this->rebelCount;
    };

    void tick(Time timeStep) {
        unsigned int newTimeValue = (this->tcurr.getTime() + timeStep.getTime()) % this->t1.getTime();
        tcurr.setTime(newTimeValue);
        if (tcurr.isAttackTime()) conductAttack();
    };
};


#endif //JNP6_BATTLE_H
