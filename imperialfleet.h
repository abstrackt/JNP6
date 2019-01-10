#ifndef JNP6_IMPERIALFLEET_H
#define JNP6_IMPERIALFLEET_H

#include "helper.h"
#include "parameters.h"

#include <utility>
#include <vector>
#include <memory>

//INTERFACE
class ImperialStarship : virtual public CombatStarship {};

class SoloImperialStarship : public virtual SoloCombatStarship,
    public virtual ImperialStarship,
    public virtual SoloStarship {
public:
    SoloImperialStarship(ShieldPoints shield, AttackPower power)
        : SoloCombatStarship(power), SoloStarship(shield) {}
};

class DeathStar : public SoloImperialStarship {
public:
    DeathStar(ShieldPoints shield, AttackPower power)
        : SoloCombatStarship(power), SoloStarship(shield), SoloImperialStarship(shield, power) {}
};

class TIEFighter : public SoloImperialStarship {
public:
    TIEFighter(ShieldPoints shield, AttackPower power)
        : SoloCombatStarship(power), SoloStarship(shield), SoloImperialStarship(shield, power) {}
};

class ImperialDestroyer : public SoloImperialStarship {
public:
    ImperialDestroyer(ShieldPoints shield, AttackPower power)
        : SoloCombatStarship(power), SoloStarship(shield), SoloImperialStarship(shield, power) {}
};

/*class Squadron : public ImperialStarship {
private:
    std::vector<ImperialStarship> members;
public:
    //TODO
    Squadron(std::initializer_list<ImperialStarship> members)
        : members(members) {};

    Squadron(std::vector<ImperialStarship> members)
        : members(std::move(members)) {};

    AttackPower getAttackPower() override {
        unsigned int combinedPower = 0;
        for (auto &ship : this->members) {
            combinedPower += ship.getAttackPower().getValue();
        }
        return combinedPower;
    }

    ShieldPoints getShield() override {
        unsigned int combinedShield = 0;
        for (auto &ship : this->members) {
            combinedShield += ship.getShield().getValue();
        }
        return combinedShield;
    }

    void takeDamage(AttackPower damage) override {
        for (auto &ship : this->members) {
            ship.takeDamage(damage);
        }
    }
};*/

std::shared_ptr<Starship> createDeathStar(ShieldPoints shield, AttackPower power) {
    return std::make_shared<DeathStar>(shield, power);
}

std::shared_ptr<Starship> createTIEFighter(ShieldPoints shield, AttackPower power) {
    return std::make_shared<TIEFighter>(shield, power);
}

std::shared_ptr<Starship> createImperialDestroyer(ShieldPoints shield, AttackPower power) {
    return std::make_shared<ImperialDestroyer>(shield, power);
}

// TODO - zle: vector/lista bedzie shared_ptr (patrz example)
// TODO i shared_ptr do Starship a nie ImperialStarship, czyli DOWNCAST ??? O NIE, TRAGEDIA
// TODO czyli nasze metody fabrykujace createXWing itp musza zwracac std::shared_ptr<XWing> ?
/*std::shared_ptr<Starship> createSquadron(std::initializer_list<ImperialStarship> members) {
    return std::make_shared<Squadron>(members);
}

std::shared_ptr<Starship> createSquadron(std::vector<ImperialStarship> members) {
    return std::make_shared<Squadron>(members);
}*/

#endif //JNP6_IMPERIALFLEET_H
