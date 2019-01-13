//
// Created by Maciek Mikuła on 11.01.19.
//

#include <cassert>
#include <iostream>
#include "imperialfleet.h"
#include "rebelfleet.h"
#include "battle.h"
#include <string>
#include <sstream>

#define TEST_NUM 301

/// 1* compilation error
/// 2* construction check
/// 3* battle check

constexpr Speed MIN_REBEL_SPEED = 299796;
constexpr Speed MAX_REBEL_SPEED = 2997960;
constexpr Speed MIN_STARCRUISER_SPEED = 99999;
constexpr Speed MAX_STARCRUISER_SPEED = 299795;


int main() {

#if TEST_NUM == 101
    {   // abstract class
        auto starship_unit = StarshipUnit();
    }
#endif

#if TEST_NUM == 102
    {   // abstract class
        auto starship = Starship();

    }
#endif

#if TEST_NUM == 103
    {   // abstract class
        auto warship_unit = WarshipUnit();
    }
#endif

#if TEST_NUM == 104
    {   // abstract class
        auto starship_fighter = StarshipFighter();
    }
#endif

#if TEST_NUM == 105
    {   // abstract class
        auto imperial_starship = ImperialStarship(100, 100);
    }
#endif

#if TEST_NUM == 106
    {   // abstract class
        auto imperial_fighter = ImperialFighter(100, 100);
    }
#endif

#if TEST_NUM == 107
    {   // abstract class
        auto rebel_starship = RebelStarship();
    }
#endif

#if TEST_NUM == 108
    {   // abstract class
        auto rebel_starship = RebelStarship();
    }
#endif

#if TEST_NUM == 201
    {
        auto death_star1 = createDeathStar(10000, 75);
        auto death_star2 = createDeathStar(10000, 75);
        auto fighter1 = createTIEFighter(50, 9);
        auto fighter2 = createTIEFighter(50, 9);
        auto destroyer1 = createImperialDestroyer(150, 20);
        auto destroyer2 = createImperialDestroyer(150, 20);

        auto squadron1 = createSquadron({death_star1, fighter1, destroyer1});
        auto squadron2 = createSquadron({death_star2, fighter2, destroyer2, squadron1});

        assert(death_star1->getAttackPower() == 75);
        assert(death_star1->getShield() == 10000);
        assert(death_star2->getAttackPower() == 75);
        assert(death_star2->getShield() == 10000);
        assert(fighter1->getAttackPower() == 9);
        assert(fighter1->getShield() == 50);
        assert(fighter2->getAttackPower() == 9);
        assert(fighter1->getShield() == 50);
        assert(destroyer1->getAttackPower() == 20);
        assert(destroyer1->getShield() == 150);
        assert(destroyer2->getAttackPower() == 20);
        assert(destroyer2->getShield() == 150);

        assert(squadron1->getUnitSize() == 3);
        assert(squadron1->getAttackPower() == 104);
        assert(squadron1->getShield() == 10200);

        assert(squadron2->getUnitSize() == 6);
        assert(squadron2->getShield() == 20400);
        assert(squadron2->getAttackPower() == 208);

        std::cout << "test 201 passed" << std::endl;
    };
#endif

#if TEST_NUM == 201
    {
        auto empty_squadron = createSquadron({});

        assert(empty_squadron->getShield() == 0);
        assert(empty_squadron->getAttackPower() == 0);
    }
#endif

#if TEST_NUM == 301
    {

        auto death_star1 = createDeathStar(10, 75);
        auto death_star2 = createDeathStar(100, 75);
        auto fighter1 = createTIEFighter(10, 9);
        auto fighter2 = createTIEFighter(50, 9);
        auto destroyer1 = createImperialDestroyer(15, 20);
        auto destroyer2 = createImperialDestroyer(150, 20);
        auto squadron1 = createSquadron({death_star1, fighter1, destroyer1});
        auto squadron2 = createSquadron({death_star2, fighter2, destroyer2, squadron1});

        auto fighter3 = createTIEFighter(50, 9);
        auto destroyer3 = createTIEFighter(150, 20);

        auto explorer = createExplorer(600, MIN_REBEL_SPEED);
        auto xwing1 = createXWing(300, MIN_REBEL_SPEED, 15);
        auto xwing2 = createXWing(100, MAX_REBEL_SPEED, 15);
        auto star_cruiser1 = createStarCruiser(100, MIN_STARCRUISER_SPEED, 2);
        auto star_cruiser2 = createStarCruiser(100, MAX_STARCRUISER_SPEED, 20);

        auto battle = SpaceBattle::Builder().
                startTime(2).
                maxTime(10).
                ship(squadron2).
                ship(fighter3).
                ship(destroyer3).
                ship(explorer).
                ship(xwing1).
                ship(xwing2).
                ship(star_cruiser1).
                ship(star_cruiser2).
                build();


        assert(battle.countImperialFleet() == 8);
        assert(battle.countRebelFleet() == 5);


        battle.tick(3); // 2 attack
        /*
         * Destroyed:
         * squadron1
         * fighter2
         *
         * star_cruiser1
         * star_cruiser2
         * xwing2
         */

        assert(battle.countImperialFleet() == 4);
        assert(battle.countRebelFleet() == 2);

        // Imperium
        assert(squadron1->getShield() == 0);
        assert(death_star1->getShield() == 0);
        assert(fighter1->getShield() == 0);
        assert(destroyer1->getShield() == 0);
        assert(fighter2->getShield() == 0);

        // Rebel
        assert(star_cruiser1->getShield() == 0);
        assert(star_cruiser2->getShield() == 0);
        assert(xwing2->getShield() == 0);

        assert(xwing1->getShield() == 63);
        assert(explorer->getShield() == 363);
        assert(death_star2->getShield() == 48);
        assert(destroyer2->getShield() == 98);
        assert(fighter3->getShield() == 35);
        assert(destroyer3->getShield() == 135);
        assert(squadron2->getShield() == 146);
        assert(squadron2->getAttackPower() == 95);

        battle.tick(1); // 5 no attack
        assert(battle.countImperialFleet() == 4);
        assert(battle.countRebelFleet() == 2);
        assert(xwing1->getShield() == 63);
        assert(explorer->getShield() == 363);
        assert(death_star2->getShield() == 48);
        assert(destroyer2->getShield() == 98);
        assert(fighter3->getShield() == 35);
        assert(destroyer3->getShield() == 135);
        assert(squadron2->getShield() == 146);
        assert(squadron2->getAttackPower() == 95);

        battle.tick(4); // 6 attack
        /*
         * xwing1 destroyed
         */
        assert(battle.countImperialFleet() == 4);
        assert(battle.countRebelFleet() == 1);
        assert(xwing1->getShield() == 0);
        assert(explorer->getShield() == 239);
        assert(death_star2->getShield() == 33);
        assert(destroyer2->getShield() == 83);
        assert(fighter3->getShield() == 35);
        assert(destroyer3->getShield() == 135);
        assert(squadron2->getShield() == 116);
        assert(squadron2->getAttackPower() == 95);

        battle.tick(1); // 10 no attack
        assert(battle.countImperialFleet() == 4);
        assert(battle.countRebelFleet() == 1);
        assert(explorer->getShield() == 239);
        assert(death_star2->getShield() == 33);
        assert(destroyer2->getShield() == 83);
        assert(fighter3->getShield() == 35);
        assert(destroyer3->getShield() == 135);
        assert(squadron2->getShield() == 116);
        assert(squadron2->getAttackPower() == 95);

        battle.tick(1); // 0 no attack
        assert(battle.countImperialFleet() == 4);
        assert(battle.countRebelFleet() == 1);
        assert(battle.countImperialFleet() == 4);
        assert(battle.countRebelFleet() == 1);
        assert(explorer->getShield() == 239);
        assert(death_star2->getShield() == 33);
        assert(destroyer2->getShield() == 83);
        assert(fighter3->getShield() == 35);
        assert(destroyer3->getShield() == 135);
        assert(squadron2->getShield() == 116);
        assert(squadron2->getAttackPower() == 95);

        battle.tick(2); // 1 no attack
        assert(battle.countImperialFleet() == 4);
        assert(battle.countRebelFleet() == 1);
        assert(explorer->getShield() == 239);
        assert(death_star2->getShield() == 33);
        assert(destroyer2->getShield() == 83);
        assert(fighter3->getShield() == 35);
        assert(destroyer3->getShield() == 135);
        assert(squadron2->getShield() == 116);
        assert(squadron2->getAttackPower() == 95);

        battle.tick(3); // 3 attack
        assert(battle.countImperialFleet() == 4);
        assert(battle.countRebelFleet() == 1);
        assert(explorer->getShield() == 115);
        assert(death_star2->getShield() == 33);
        assert(destroyer2->getShield() == 83);
        assert(fighter3->getShield() == 35);
        assert(destroyer3->getShield() == 135);
        assert(squadron2->getShield() == 116);
        assert(squadron2->getAttackPower() == 95);

        battle.tick(10101); // 6 attack
        /*
         * explorer destroyed
         */
        assert(battle.countImperialFleet() == 4);
        assert(battle.countRebelFleet() == 0);
        assert(explorer->getShield() == 0);
        assert(death_star2->getShield() == 33);
        assert(destroyer2->getShield() == 83);
        assert(fighter3->getShield() == 35);
        assert(destroyer3->getShield() == 135);
        assert(squadron2->getShield() == 116);
        assert(squadron2->getAttackPower() == 95);



        std::cout << "test 202 passed" << std::endl;
    }
#endif

    return 0;
}