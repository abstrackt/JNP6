#ifndef JNP6_REBELFLEET_H
#define JNP6_REBELFLEET_H

#include "imperialfleet.h"
#include "helper.h"

class RebelStarship : public SoloStarship {
private:
    Speed speed;
public:
    RebelStarship(ShieldPoints shield, Speed speed) : SoloStarship(shield) {
        this->speed = speed;
    };

    Speed getSpeed() const {
        return this->speed;
    };

    virtual void engageTarget(ImperialStarship &s) {
        this->takeDamage(s.getAttackPower());
    };
};

class Explorer : public RebelStarship {
public:
    Explorer(ShieldPoints shield, Speed speed) : RebelStarship(shield, speed){};
};

class XWing : public RebelCombatStarship {
public:
    XWing(ShieldPoints shield, Speed speed, AttackPower power) : RebelCombatStarship(shield, speed, power){};
};

class StarCruiser : public RebelCombatStarship {
public:
    StarCruiser(ShieldPoints shield, Speed speed, AttackPower power) : RebelCombatStarship(shield, speed, power){};
};

#endif //JNP6_REBELFLEET_H

