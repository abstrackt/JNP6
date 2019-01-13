#ifndef JNP6_BATTLE_H
#define JNP6_BATTLE_H

#include "imperialfleet.h"
#include "rebelfleet.h"

#include <vector>
#include <iostream>

class Clock {
private:
    unsigned int tcurr;
    unsigned int t1;

public:
    Clock(unsigned int t0, unsigned int t1) {
        this->tcurr = t0;
        this->t1 = t1;
    }

    virtual unsigned int getTime() {
        return this->tcurr;
    };

    virtual void tickTime(unsigned int timeStep) {
        unsigned int newTimeValue = (this->tcurr + timeStep) % this->t1;
        this->tcurr = newTimeValue;
    };

    virtual bool isAttackTime() {
        return (this->tcurr % 2 == 0 ||
               this->tcurr % 3 == 0) &&
               this->tcurr % 5 != 0;
    };
};

class SpaceBattle {

private:
    std::vector<std::shared_ptr<ImperialStarship>> imperialForce;
    std::vector<std::shared_ptr<RebelStarship>> rebelForce;
    Clock c;

    SpaceBattle(unsigned int t0, unsigned int t1, std::vector<std::shared_ptr<ImperialStarship>> const &iForce,
                std::vector<std::shared_ptr<RebelStarship>> const &rForce) : c(t0, t1) {
        this->imperialForce = iForce;
        this->rebelForce = rForce;
    };

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
        unsigned int t0;
        unsigned int t1;

    public:
        Builder() {
            this->t0 = 0;
            this->t1 = 0;
        }

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
            t0 = x;
            return *this;
        }

        Builder &maxTime(unsigned int x) {
            t1 = x;
            return *this;
        }

        SpaceBattle build() const {
            return SpaceBattle(t0, t1, imperialForce, rebelForce);
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

    void tick(unsigned int timeStep) {
        size_t imperialCount = countImperialFleet();
        size_t rebelCount = countRebelFleet();
        if(imperialCount == 0 && rebelCount == 0) std::cout << "DRAW\n";
        if(imperialCount == 0 && rebelCount != 0) std::cout << "REBELLION WON\n";
        if(imperialCount != 0 && rebelCount == 0) std::cout << "IMPERIUM WON\n";
        if (c.isAttackTime()) {
            conductAttack();
        }
        c.tickTime(timeStep);
    }
};


#endif //JNP6_BATTLE_H
