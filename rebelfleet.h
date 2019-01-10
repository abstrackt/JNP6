#ifndef JNP6_REBELFLEET_H
#define JNP6_REBELFLEET_H

#include <memory>
#include "helper.h"
#include "imperialfleet.h"

class RebelStarship : virtual public SoloStarship {
private:
    Speed speed;
public:
    RebelStarship(ShieldPoints shield, Speed speed) : SoloStarship(shield), speed(speed) {}

    // TODO niescislosc? getSpeed() jest z const a getShield() nie
    // TODO i getSpeed() nie jest virtual a getShield() jest, czyli potencjalnie
    // TODO zabraniamy pozniejsza modyfikacje tego
    Speed getSpeed() const {
        return this->speed;
    }

    virtual void engageTarget(SoloImperialStarship &s) {
        this->takeDamage(s.getAttackPower());
    }
};

class RebelCombatStarship : virtual public SoloCombatStarship,
    virtual public RebelStarship {
public:
    RebelCombatStarship(ShieldPoints shield, AttackPower power, Speed speed)
        : SoloCombatStarship(power), SoloStarship(shield), RebelStarship(shield, speed) {}

    void engageTarget(SoloImperialStarship &s) override {
        this->takeDamage(s.getAttackPower());
        s.takeDamage(this->getAttackPower());
    }
};

class Explorer : public RebelStarship {
public:
    Explorer(ShieldPoints shield, Speed speed)
        : SoloStarship(shield), RebelStarship(shield, speed) {
        assert(299796 <= speed.getValue() && speed.getValue() <= 2997960);
    }
};

class XWing : public RebelCombatStarship {
public:
    XWing(ShieldPoints shield, Speed speed, AttackPower power)
        : SoloCombatStarship(power),
        SoloStarship(shield),
        RebelStarship(shield, speed),
        RebelCombatStarship(shield, power, speed) {
        assert(299796 <= speed.getValue() && speed.getValue() <= 2997960);
    }
};

class StarCruiser : public RebelCombatStarship {
public:
    StarCruiser(ShieldPoints shield, Speed speed, AttackPower power)
        : SoloCombatStarship(power),
        SoloStarship(shield),
        RebelStarship(shield, speed),
        RebelCombatStarship(shield, power, speed) {
        assert(99999 <= speed.getValue() && speed.getValue() <= 299795);
    }
};

std::shared_ptr<Explorer> createExplorer(ShieldPoints shield, Speed speed) {
    return std::make_shared<Explorer>(shield, speed);
}

std::shared_ptr<XWing> createXWing(ShieldPoints shield, Speed speed, AttackPower power) {
    return std::make_shared<XWing>(shield, speed, power);
}

std::shared_ptr<StarCruiser> createStarCruiser(ShieldPoints shield, Speed speed, AttackPower power) {
    return std::make_shared<StarCruiser>(shield, speed, power);
}

#endif //JNP6_REBELFLEET_H

