#ifndef JNP6_BATTLE_H
#define JNP6_BATTLE_H

#include "imperialfleet.h"
#include "rebelfleet.h"

#include <vector>
#include <iostream>

using Time = unsigned long long;

class Clock {
private:
    Time t0, t1, currentTime;

public:
    Clock(const Time &t0, const Time &t1) : t0(t0), t1(t1), currentTime(t0) {}

    virtual ~Clock() = default;

    virtual void stepTime(const Time &timeStep) {
        auto newTimeValue = (this->currentTime + timeStep) % (this->t1 + 1);
        this->currentTime = newTimeValue;
    }

    virtual Time getCurrentTime() const {
        return this->currentTime;
    }

    virtual bool isAttackTime() const {
        return (this->currentTime % 2 == 0 ||
                this->currentTime % 3 == 0) && this->currentTime % 5 != 0;
    }
};

class SpaceBattle {
private:
    std::vector<ImperialStarship_ptr> imperialForce;
    std::vector<RebelStarship_ptr> rebelForce;
    Clock clock;

    SpaceBattle(const Time &t0, const Time &t1,
                std::vector<ImperialStarship_ptr> imperialForce,
                std::vector<RebelStarship_ptr> rebelForce)
        : imperialForce(std::move(imperialForce)), rebelForce(std::move(rebelForce)),
        clock(t0, t1) {}

    void conductAttack() {
        for (auto &iShip : imperialForce) {
            for (auto &rShip : rebelForce) {
                auto shouldAttack = rShip->getShield() != 0
                    && iShip->getShield() != 0;

                if (shouldAttack) rShip->engageTarget(*iShip);
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
        Builder() : t0(0), t1(0) {}

        Builder &ship(const RebelStarship_ptr &starship) {
            rebelForce.push_back(starship);
            return *this;
        }

        Builder &ship(const ImperialStarship_ptr &starship) {
            imperialForce.push_back(starship);
            return *this;
        }

        Builder &startTime(const Time &t0) {
            this->t0 = t0;
            return *this;
        }

        Builder &maxTime(const Time &t1) {
            this->t1 = t1;
            return *this;
        }

        SpaceBattle build() const {
            return SpaceBattle(t0, t1, imperialForce, rebelForce);
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
        auto imperialCount = this->countImperialFleet();
        auto rebelCount = this->countRebelFleet();

        if (imperialCount == 0 && rebelCount == 0) std::cout << "DRAW\n";
        if (imperialCount == 0 && rebelCount != 0) std::cout << "REBELLION WON\n";
        if (imperialCount != 0 && rebelCount == 0) std::cout << "IMPERIUM WON\n";

        if (this->clock.isAttackTime()) {
            conductAttack();
        }
        this->clock.stepTime(timeStep);
    }
};


#endif //JNP6_BATTLE_H