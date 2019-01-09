//
// Created by Andrzej on 06.01.2019.
//

#include "rebelfleet.h"

RebelStarship::RebelStarship(ShieldPoints shield, Speed speed)
    : Starship(shield), speed(speed) {}

Explorer::Explorer(ShieldPoints shield, Speed speed) : RebelStarship(shield, speed) {}

XWing::XWing(ShieldPoints shield, Speed speed, AttackPower power)
    : RebelStarship(shield, speed), CombatStarship(shield, power) {}

StarCruiser::StarCruiser(ShieldPoints shield, Speed speed, AttackPower power)
    : RebelStarship(shield, speed), CombatStarship(shield, power) {}

// czy shared_ptr<Starship> czy shared_ptr<Explorer> zwracac?
std::shared_ptr<Starship> createExplorer(ShieldPoints shield, Speed speed) {
    return std::make_shared<Explorer>(shield, speed);
}

std::shared_ptr<Starship> createXWing(ShieldPoints shield, Speed speed, AttackPower power) {
    // TODO to jest jakis bullshit chyba? ale nawet sie kompiluje, czyli
    // udowodnione matematycznie ze jest poprawne
    return std::dynamic_pointer_cast<RebelStarship>(
        std::make_shared<XWing>(shield, speed, power));
}

std::shared_ptr<Starship> createStarCruiser(ShieldPoints shield, Speed speed, AttackPower power) {
    return std::dynamic_pointer_cast<RebelStarship>(
        std::make_shared<StarCruiser>(shield, speed, power));
}
