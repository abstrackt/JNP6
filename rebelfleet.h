//
// Created by Andrzej on 06.01.2019.
//

#ifndef JNP6_REBELFLEET_H
#define JNP6_REBELFLEET_H

#include "helper.h"
#include <memory>

class RebelStarship : public Starship {
private:
    Speed speed;

protected:
    RebelStarship(ShieldPoints shield, Speed speed);
public:
    Speed getSpeed() const;
};

class Explorer : public RebelStarship {
public:
    Explorer(ShieldPoints shield, Speed speed);
};

class XWing : public RebelStarship, public CombatStarship {
public:
    XWing(ShieldPoints shield, Speed speed, AttackPower power);
};

class StarCruiser : public RebelStarship, public CombatStarship {
public:
    StarCruiser(ShieldPoints shield, Speed speed, AttackPower power);
};


std::shared_ptr<Starship> createExplorer(ShieldPoints shield, Speed speed);
std::shared_ptr<Starship> createXWing(ShieldPoints shield, Speed speed, AttackPower power);
std::shared_ptr<Starship> createStarCruiser(ShieldPoints shield, Speed speed, AttackPower power);

#endif //JNP6_REBELFLEET_H
