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

    virtual unsigned int getTime() const {
        return this->value;
    };

    virtual bool isAttackTime() {
        return (this->value % 2 == 0 ||
                this->value % 3 == 0) &&
            this->value % 5 != 0;
    };
};

class Clock {
private:
    Time t0, t1, currentTime;

public:
    Clock(const Time &t0, const Time &t1) : t0(t0), t1(t1), currentTime(t0) {}

    void stepTime(const Time &timeStep) {
        auto newTimeValue = (this->currentTime.getTime() + timeStep.getTime()) % this->t1.getTime();
        this->currentTime = newTimeValue;
    }

    Time getCurrentTime() const {
        return this->currentTime;
    }
};

class SpaceBattle {
private:
    std::vector<ImperialStarship_ptr> imperialForce;
    std::vector<RebelStarship_ptr> rebelForce;
    Clock clock;

    SpaceBattle(Time t0, Time t1, std::vector<ImperialStarship_ptr> iForce,
                std::vector<RebelStarship_ptr> rForce)
        : rebelForce(rForce), imperialForce(iForce), clock(t0, t1) {}

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
        std::vector<ImperialStarship_ptr> imperialForce;
        std::vector<RebelStarship_ptr> rebelForce;
        Time t0, t1;

    public:
        Builder() : t0(Time(0)), t1(Time(0)) {}

        Builder &ship(RebelStarship_ptr starship) {
            RebelStarship_ptr moved = std::move(starship);
            rebelForce.push_back(moved);
            return *this;
        }

        Builder &ship(ImperialStarship_ptr starship) {
            ImperialStarship_ptr moved = std::move(starship);
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
            count += ship->getCount();
        }
        return count;
    }

    size_t countRebelFleet() {
        size_t count = 0;
        for (auto &ship : rebelForce) {
            count += ship->getCount();
        }
        return count;
    }

    void tick(const Time &timeStep) {
        auto imperialCount = countImperialFleet();
        auto rebelCount = countRebelFleet();
        if (imperialCount == 0 && rebelCount == 0) std::cout << "DRAW\n";
        if (imperialCount == 0 && rebelCount != 0) std::cout << "REBELLION WON\n";
        if (imperialCount != 0 && rebelCount == 0) std::cout << "IMPERIUM WON\n";

        auto currentTime = clock.getCurrentTime();

        if (currentTime.isAttackTime()) {
            std::cout << "fighting now\n";
            conductAttack();
        }
        this->clock.stepTime(timeStep);
        std::cout << "at time " << currentTime.getTime() <<
            " rebels: " << countRebelFleet() <<
            " imperials: " << countImperialFleet() << "\n";
    }
};


#endif //JNP6_BATTLE_H
