#ifndef JNP6_IMPERIALFLEET_H
#define JNP6_IMPERIALFLEET_H

#include "helper.h"

//INTERFACE
class ImperialStarship : public CombatStarship {

};

class DeathStar : public SoloImperialStarship {
public:
    DeathStar(ShieldPoints shield, AttackPower power) : SoloImperialStarship(shield, power) {};
};

class TIEFighter : public SoloImperialStarship {
public:
    TIEFighter(ShieldPoints shield, AttackPower power) : SoloImperialStarship(shield, power) {};
};

class ImperialDestroyer : public SoloImperialStarship {
public:
    ImperialDestroyer(ShieldPoints shield, AttackPower power) : SoloImperialStarship(shield, power) {};
};

class Squadron : public ImperialStarship {
private:
    vector<ImperialStarship &> members;
public:
    //TODO
    Squadron(ImperialShip &s...) {};

    AttackPower getAttackPower() override {
        unsigned int combined_power = 0;
        for(auto &ship : members) {
            combined_power += ship.getAttackPower().getValue();
        }
    };

    ShieldPoints getShield() override {

    };

    void takeDamage(AttackPower damage) override {

    };
};

#endif //JNP6_IMPERIALFLEET_H
