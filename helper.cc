//
// Created by Andrzej on 07.01.2019.
//

#include <algorithm>
#include "helper.h"

AttackPower::AttackPower(unsigned power) : power(power) {}

ShieldPoints::ShieldPoints(unsigned points) : points(points) {}

void ShieldPoints::decreaseShield(AttackPower value) {
    this->points -= std::min(value.power, this->points);
}

Speed::Speed(unsigned speed) : speed(speed) {}

void Starship::attack(Starship &s) {

}

void Starship::takeDamage(AttackPower damage) {
    this->shield.decreaseShield(damage);
}

Starship::Starship(ShieldPoints shield) : shield(shield) {}

ShieldPoints Starship::getShield() {
    return this->shield;
}

CombatStarship::CombatStarship(ShieldPoints shield, AttackPower power)
    : Starship(shield), power(power) {}

void CombatStarship::attack(Starship &s) {
    s.takeDamage(this->getAttackPower());
}

AttackPower CombatStarship::getAttackPower() {
    return this->power;
}