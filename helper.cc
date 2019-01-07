//
// Created by Andrzej on 07.01.2019.
//

#include <algorithm>
#include "helper.h"

void ShieldPoints::decreaseShield(AttackPower value) {
    this->points -= std::min(value.power, this->points);
}

void Starship::attack(Starship &s) {

}

void Starship::takeDamage(AttackPower damage) {
    this->shield.decreaseShield(damage);
}

ShieldPoints Starship::getShield() {
    return this->shield;
}

void CombatStarship::attack(Starship &s) {
    s.takeDamage(this->getAttackPower());
}

AttackPower CombatStarship::getAttackPower() {
    return this->power;
}


