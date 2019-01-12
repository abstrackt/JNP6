#include "imperialfleet.h"
#include "rebelfleet.h"
#include "battle.h"

#include <cassert>
#include <iostream>

int main() {
    auto xwing = createXWing(100, 300000, 50);
    auto explorer = createExplorer(150, 400000);
    auto cruiser = createStarCruiser(1234, 100000, 11);
    std::cout << "xwing: " << xwing->getShield().getValue() << std::endl;
    std::cout << "explorer: " << explorer->getShield().getValue() << std::endl;
    std::cout << "cruiser: " << cruiser->getShield().getValue() << std::endl;
    auto deathStar = createDeathStar(10000, 75);
    auto fighter = createTIEFighter(50, 9);
    auto destroyer = createImperialDestroyer(150, 20);
    auto squadron = createSquadron({deathStar, fighter});

    auto battle = SpaceBattle::Builder()
        .ship(squadron)
        .startTime(2)
        .maxTime(23)
        .ship(xwing)
        .ship(explorer)
        .build();

    std::cout << "rebels: " << battle.countRebelFleet() << "\n";
    std::cout << "imperials: " << battle.countImperialFleet() << "\n";

    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 2);

    battle.tick(3);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 1);

    battle.tick(1);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 1);

    battle.tick(4);
    assert(battle.countRebelFleet() == 0);
    assert(battle.countImperialFleet() == 1);

    battle.tick(1); // Wypisuje "IMPERIUM WON\n". */
}
