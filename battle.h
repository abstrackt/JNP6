#ifndef JNP6_BATTLE_H
#define JNP6_BATTLE_H

#include "imperialfleet.h"
#include "rebelfleet.h"

#include <vector>
#include <iostream>

class Time {
private:
    unsigned int value;

public:
    Time(unsigned int start) {
        this->value = start;
    }

    virtual unsigned int getTime() {
        return this->value;
    };

    virtual void setTime(unsigned int newTime) {
        this->value = newTime;
    };

    virtual bool isAttackTime() {
        return (this->value % 2 == 0 ||
               this->value % 3 == 0) &&
               this->value % 5 != 0;
    };
};

class SpaceBattle {

private:
    std::vector<std::shared_ptr<ImperialStarship>> imperialForce;
    std::vector<std::shared_ptr<RebelStarship>> rebelForce;
    Time t0, t1, tcurr;

    SpaceBattle(Time t0, Time t1, std::vector<std::shared_ptr<ImperialStarship>> iForce,
                std::vector<std::shared_ptr<RebelStarship>> rForce)
                    : t0(t0), t1(t1), tcurr(t0), rebelForce(rForce),
                      imperialForce(iForce) {};

    void conductAttack() {
        for (auto &iShip : imperialForce) {
            for (auto &rShip : rebelForce) {
                if (rShip->getShield().getValue() != 0 && iShip->getShield().getValue() != 0) {
                    rShip->engageTarget(*iShip);
                }
            }
        }
    };

public:
    class Builder {
    private:
        std::vector<std::shared_ptr<ImperialStarship>> imperialForce;
        std::vector<std::shared_ptr<RebelStarship>> rebelForce;
        Time t0, t1;

    public:
        Builder() : t0(Time(0)), t1(Time(0)) {}

        Builder &ship(std::shared_ptr<RebelStarship> starship) {
            std::shared_ptr<RebelStarship> moved = std::move(starship);
            rebelForce.push_back(moved);
            return *this;
        }

        Builder &ship(std::shared_ptr<ImperialStarship> starship) {
            std::shared_ptr<ImperialStarship> moved = std::move(starship);
            imperialForce.push_back(moved);
            return *this;
        }

        Builder &ship(std::shared_ptr<Squadron> starship) {
            std::shared_ptr<Squadron> moved = std::move(starship);
            imperialForce.push_back(moved);
            return *this;
        }

        Builder &startTime(unsigned int x) {
            t0 = Time(x);
            return *this;
        }

        Builder &maxTime(unsigned int x) {
            t1 = Time(x);
            return *this;
        }

        SpaceBattle &build() {
            SpaceBattle *s = new SpaceBattle(t0, t1, imperialForce, rebelForce);
            return *s;
        }
    };

    size_t countImperialFleet() {
        size_t count = 0;
        for (auto &ship : imperialForce) {
            count+=ship->getCount();
        }
        return count;
    }

    size_t countRebelFleet() {
        size_t count = 0;
        for (auto &ship : rebelForce) {
            count+=ship->getCount();
        }
        return count;
    }

    void tick(Time timeStep) {
        size_t imperialCount = countImperialFleet();
        size_t rebelCount = countRebelFleet();
        if(imperialCount == 0 && rebelCount == 0) std::cout << "DRAW\n";
        if(imperialCount == 0 && rebelCount != 0) std::cout << "REBELLION WON\n";
        if(imperialCount != 0 && rebelCount == 0) std::cout << "IMPERIUM WON\n";
        if (tcurr.isAttackTime()) {
            std::cout << "fighting now\n";
            conductAttack();
        }
        unsigned int newTimeValue = (this->tcurr.getTime() + timeStep.getTime()) % this->t1.getTime();
        tcurr.setTime(newTimeValue);
        std::cout << "at time " << tcurr.getTime() <<
                     " rebels: " << countRebelFleet() <<
                     " imperials: " << countImperialFleet() << "\n";
    }
};


#endif //JNP6_BATTLE_H
