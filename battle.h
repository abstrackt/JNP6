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
        return this->value % 2 == 0 &&
               this->value % 3 == 0 &&
               this->value % 5 != 0;
    };
};

class SpaceBattle {

private:
    std::vector<std::shared_ptr<ImperialStarship>> imperialForce;
    std::vector<std::shared_ptr<RebelStarship>> rebelForce;
    size_t imperialCount, rebelCount;
    Time t0, t1, tcurr;

    SpaceBattle(size_t ic, size_t rc, Time t0, Time t1,
                std::vector<std::shared_ptr<ImperialStarship>> iForce,
                std::vector<std::shared_ptr<RebelStarship>> rForce)
                    : imperialCount(ic),
                      rebelCount(rc), t0(t0),
                      t1(t1), tcurr(t0), rebelForce(rForce),
                      imperialForce(iForce) {};

    void conductAttack() {
        for (auto &iShip : imperialForce) {
            for (auto &rShip : rebelForce) {
                if (rShip->getShield().getValue() != 0 && iShip->getShield().getValue() != 0) {
                    rShip->engageTarget(*iShip);
                    if (rShip->getShield().getValue() == 0) rebelCount--;
                    if (iShip->getShield().getValue() == 0) imperialCount--;
                }
            }
        }
    };

public:
    class Builder {
    private:
        std::vector<std::shared_ptr<ImperialStarship>> imperialForce;
        std::vector<std::shared_ptr<RebelStarship>> rebelForce;
        size_t imperialCount, rebelCount;
        Time t0, t1;

    public:
        Builder() : imperialCount(0), rebelCount(0),
                    t0(Time(0)), t1(Time(0)) {}

        Builder &ship(std::shared_ptr<RebelStarship> starship) {
            std::shared_ptr<RebelStarship> moved = std::move(starship);
            rebelForce.push_back(moved);
            rebelCount++;
            return *this;
        }

        Builder &ship(std::shared_ptr<ImperialStarship> starship) {
            std::shared_ptr<ImperialStarship> moved = std::move(starship);
            imperialForce.push_back(moved);
            imperialCount++;
            return *this;
        }

        Builder &ship(std::shared_ptr<Squadron> starship) {
            std::shared_ptr<Squadron> moved = std::move(starship);
            imperialForce.push_back(moved);
            //TODO jak dostać się do liczebności squadronu bez publicznych zmiennych?
            //TODO czy jeżeli do bitwy dodany zostaje squadron to możemy założyć że nie zostaną
            //oddzielnie dodane do niej statki należące do squadronu?
            imperialCount++;
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
            SpaceBattle *s = new SpaceBattle(imperialCount, rebelCount,
                                             t0, t1, imperialForce, rebelForce);
            return *s;
        }
    };

    size_t countImperialFleet() {
        return this->imperialCount;
    }

    size_t countRebelFleet() {
        return this->rebelCount;
    }

    void tick(Time timeStep) {
        if(imperialCount == 0 && rebelCount == 0) std::cout << "DRAW\n";
        if(imperialCount == 0 && rebelCount != 0) std::cout << "REBELLION WON\n";
        if(imperialCount != 0 && rebelCount == 0) std::cout << "IMPERIUM WON\n";
        unsigned int newTimeValue = (this->tcurr.getTime() + timeStep.getTime()) % this->t1.getTime();
        tcurr.setTime(newTimeValue);
        if (tcurr.isAttackTime()) conductAttack();
    }
};


#endif //JNP6_BATTLE_H
