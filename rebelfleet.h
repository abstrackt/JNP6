#ifndef JNP6_REBELFLEET_H
#define JNP6_REBELFLEET_H

#include <memory>
#include "imperialfleet.h"
#include "helper.h"

class RebelStarship : virtual public SoloStarship {
private:
    Speed speed;
public:
    RebelStarship(ShieldPoints shield, Speed speed) : SoloStarship(shield), speed(speed) {}

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
    RebelCombatStarship(ShieldPoints shield, AttackPower power, Speed speed) : SoloStarship(shield),
                                                                               RebelStarship(shield, speed),
                                                                               SoloCombatStarship(power) {}

    void engageTarget(SoloImperialStarship &s) override {
        this->takeDamage(s.getAttackPower());
        s.takeDamage(this->getAttackPower());
    }
};

class Explorer : public RebelStarship {
public:
    Explorer(ShieldPoints shield, Speed speed) : RebelStarship(shield, speed),
                                                 SoloStarship(shield) {}
};

class XWing : public RebelCombatStarship {
public:
    XWing(ShieldPoints shield, Speed speed, AttackPower power) : RebelCombatStarship(shield, power, speed),
                                                                 SoloStarship(shield),
                                                                 RebelStarship(shield, speed),
                                                                 SoloCombatStarship(power) {}
};

class StarCruiser : public RebelCombatStarship {
public:
    StarCruiser(ShieldPoints shield, Speed speed, AttackPower power) : RebelCombatStarship(shield, power, speed),
                                                                       SoloStarship(shield),
                                                                       RebelStarship(shield, speed),
                                                                       SoloCombatStarship(power) {}
};

// czy shared_ptr<Starship> czy shared_ptr<Explorer> zwracac?
std::shared_ptr<Starship> createExplorer(ShieldPoints shield, Speed speed) {
    return std::make_shared<Explorer>(shield, speed);
}

std::shared_ptr<Starship> createXWing(ShieldPoints shield, Speed speed, AttackPower power) {
    // TODO to jest jakis bullshit chyba? ale nawet sie kompiluje, czyli
    // TODO udowodnione matematycznie ze jest poprawne
    return std::dynamic_pointer_cast<RebelStarship>(
            std::make_shared<XWing>(shield, speed, power));
}

std::shared_ptr<Starship> createStarCruiser(ShieldPoints shield, Speed speed, AttackPower power) {
    return std::dynamic_pointer_cast<RebelStarship>(
            std::make_shared<StarCruiser>(shield, speed, power));
}

#endif //JNP6_REBELFLEET_H

