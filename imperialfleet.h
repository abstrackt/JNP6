#ifndef JNP6_IMPERIALFLEET_H
#define JNP6_IMPERIALFLEET_H

#include "helper.h"
#include "parameters.h"
#include <vector>

//INTERFACE
class ImperialStarship : virtual public CombatStarship {

};

class SoloImperialStarship : public virtual SoloCombatStarship,
                             public virtual ImperialStarship,
                             public virtual SoloStarship {
public:
    SoloImperialStarship(ShieldPoints shield, AttackPower power) : SoloStarship(shield),
                                                                   SoloCombatStarship(power) {}
};

class DeathStar : public SoloImperialStarship {
public:
    DeathStar(ShieldPoints shield, AttackPower power) : SoloImperialStarship(shield, power),
                                                        SoloStarship(shield),
                                                        SoloCombatStarship(power) {};
};

class TIEFighter : public SoloImperialStarship {
public:
    TIEFighter(ShieldPoints shield, AttackPower power) : SoloImperialStarship(shield, power),
                                                         SoloStarship(shield),
                                                         SoloCombatStarship(power) {};
};

class ImperialDestroyer : public SoloImperialStarship {
public:
    ImperialDestroyer(ShieldPoints shield, AttackPower power) : SoloImperialStarship(shield, power),
                                                                SoloStarship(shield),
                                                                SoloCombatStarship(power) {};
};

class Squadron : public ImperialStarship {
private:
    std::vector<ImperialStarship> members;
public:
    //TODO
    Squadron(ImperialStarship &s...) {};

    AttackPower getAttackPower() override {
        unsigned int combined_power = 0;
        for (auto &ship : members) {
            combined_power += ship.getAttackPower().getValue();
        }
    };

    ShieldPoints getShield() override {

    };

    void takeDamage(AttackPower damage) override {

    };
};

#endif //JNP6_IMPERIALFLEET_H
