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

class Squadron : public ImperialStarship {
private:
    // TODO: tutaj dobrze using??
    std::vector<std::shared_ptr<ImperialStarship>> members;
public:
    //TODO
    Squadron(std::initializer_list<std::shared_ptr<ImperialStarship>> members)
        : members(members) {};

    Squadron(std::vector<std::shared_ptr<ImperialStarship>> members)
        : members(std::move(members)) {};

    AttackPower getAttackPower() override {
        unsigned int combinedPower = 0;
        for (auto &ship : this->members) {
            combinedPower += ship->getAttackPower().getValue();
        }
        return combinedPower;
    }

    ShieldPoints getShield() override {
        unsigned int combinedShield = 0;
        for (auto &ship : this->members) {
            combinedShield += ship->getShield().getValue();
        }
        return combinedShield;
    }

    void takeDamage(AttackPower damage) override {
        for (auto &ship : this->members) {
            ship->takeDamage(damage);
        }
    }
};

std::shared_ptr<DeathStar> createDeathStar(ShieldPoints shield, AttackPower power) {
    return std::make_shared<DeathStar>(shield, power);
}

std::shared_ptr<TIEFighter> createTIEFighter(ShieldPoints shield, AttackPower power) {
    return std::make_shared<TIEFighter>(shield, power);
}

std::shared_ptr<ImperialDestroyer> createImperialDestroyer(ShieldPoints shield, AttackPower power) {
    return std::make_shared<ImperialDestroyer>(shield, power);
}

std::shared_ptr<ImperialStarship> createSquadron(std::initializer_list<std::shared_ptr<ImperialStarship>> members) {
    return std::make_shared<Squadron>(members);
}

std::shared_ptr<ImperialStarship> createSquadron(std::vector<std::shared_ptr<ImperialStarship>> members) {
    return std::make_shared<Squadron>(members);
}

#endif //JNP6_IMPERIALFLEET_H
