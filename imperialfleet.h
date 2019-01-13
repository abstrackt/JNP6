#ifndef JNP6_IMPERIALFLEET_H
#define JNP6_IMPERIALFLEET_H

#include "helper.h"

#include <utility>
#include <vector>
#include <memory>

class ImperialStarship : virtual public CombatStarship {};

using ImperialStarship_ptr = std::shared_ptr<ImperialStarship>;

class SoloImperialStarship : virtual public SoloCombatStarship,
                             virtual public ImperialStarship,
                             virtual public SoloStarship {
public:
    SoloImperialStarship(ShieldPoints shield, AttackPower power)
        : SoloCombatStarship(power),
        SoloStarship(shield) {}
};

class DeathStar : public SoloImperialStarship {
public:
    DeathStar(ShieldPoints shield, AttackPower power)
        : SoloCombatStarship(power),
        SoloStarship(shield),
        SoloImperialStarship(shield, power) {}
};

class TIEFighter : public SoloImperialStarship {
public:
    TIEFighter(ShieldPoints shield, AttackPower power)
        : SoloCombatStarship(power),
        SoloStarship(shield),
        SoloImperialStarship(shield, power) {}
};

class ImperialDestroyer : public SoloImperialStarship {
public:
    ImperialDestroyer(ShieldPoints shield, AttackPower power)
        : SoloCombatStarship(power),
        SoloStarship(shield),
        SoloImperialStarship(shield, power) {}
};

class Squadron : public ImperialStarship {
private:
    std::vector<ImperialStarship_ptr> members;
public:
    size_t getCount() const override {
        size_t strength = 0;
        for (auto &m : members) {
            if (m->getShield() > 0) strength += m->getCount();
        }
        return strength;
    }

    Squadron(std::initializer_list<ImperialStarship_ptr> members)
        : members(members) {}

    Squadron(std::vector<ImperialStarship_ptr> members)
        : members(std::move(members)) {}

    AttackPower getAttackPower() const override {
        AttackPower combinedPower = 0;
        for (auto &ship : this->members) {
            if (ship->getShield() > 0) {
                combinedPower += ship->getAttackPower();
            }
        }
        return combinedPower;
    }

    ShieldPoints getShield() const override {
        ShieldPoints combinedShield = 0;
        for (auto &ship : this->members) {
            combinedShield += ship->getShield();
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

std::shared_ptr<Squadron> createSquadron(std::initializer_list<ImperialStarship_ptr> members) {
    return std::make_shared<Squadron>(members);
}

std::shared_ptr<Squadron> createSquadron(std::vector<ImperialStarship_ptr> members) {
    return std::make_shared<Squadron>(members);
}

#endif //JNP6_IMPERIALFLEET_H
