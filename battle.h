//
// Created by Andrzej on 06.01.2019.
//

#ifndef JNP6_BATTLE_H
#define JNP6_BATTLE_H


#include <cstdio>

class Time {
private:
    unsigned int value;

public:
    virtual void getTime();

    virtual void advanceTime(unsigned int steps);

    virtual bool isAttackTime();
};

class SpaceBattle {
private:
    size_t imperialCount, rebelCount;
    Time t0, t1;

public:
    size_t countImperialFleet();
    size_t countRebelFleet();
    void tick(Time timeStep);
};


#endif //JNP6_BATTLE_H
