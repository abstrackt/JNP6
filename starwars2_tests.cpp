#include "battle.h"

#define BOOST_TEST_MODULE starwars2
#include <boost/test/included/unit_test.hpp>

std::string captureStdOut(std::function<void()> f) {
    boost::test_tools::output_test_stream output;
    auto old = std::cout.rdbuf(output.rdbuf());

    f();

    std::cout.rdbuf(old);
    return output.str();
}

#define BOOST_CHECK_COUT(x, y) BOOST_CHECK_EQUAL(captureStdOut([&](){x;}), (y))

BOOST_AUTO_TEST_CASE(sampleBattle) {
    auto xwing = createXWing(100, 300000, 50);
    auto explorer = createExplorer(150, 400000);
    auto cruiser = createStarCruiser(1234, 100000, 11);
    auto deathStar = createDeathStar(10000, 75);
    auto fighter = createTIEFighter(50, 9);
    auto destroyer = createImperialDestroyer(150, 20);
    auto squadron = createSquadron({ deathStar, fighter });

    auto battle = SpaceBattle::Builder()
        .ship(squadron)
        .startTime(2)
        .maxTime(23)
        .ship(xwing)
        .ship(explorer)
        .build();

    BOOST_CHECK_EQUAL(battle.countRebelFleet(), 2);
    BOOST_CHECK_EQUAL(battle.countImperialFleet(), 2);

    BOOST_CHECK_COUT(battle.tick(3), "");
    BOOST_CHECK_EQUAL(battle.countRebelFleet(), 2);
    BOOST_CHECK_EQUAL(battle.countImperialFleet(), 1);

    BOOST_CHECK_COUT(battle.tick(1), "");
    BOOST_CHECK_EQUAL(battle.countRebelFleet(), 2);
    BOOST_CHECK_EQUAL(battle.countImperialFleet(), 1);

    BOOST_CHECK_COUT(battle.tick(4), "");
    BOOST_CHECK_EQUAL(battle.countRebelFleet(), 0);
    BOOST_CHECK_EQUAL(battle.countImperialFleet(), 1);

    BOOST_CHECK_COUT(battle.tick(1), "IMPERIUM WON\n"); // "IMPERIUM WON\n".
}

BOOST_AUTO_TEST_CASE(noAttackBattle) {
    auto battle = SpaceBattle::Builder()
        .startTime(0)
        .maxTime(99)
        /* Imperials. */
        .ship(createDeathStar(100, 5))
        .ship(createTIEFighter(53, 7))
        .ship(createTIEFighter(53, 7))
        .ship(createImperialDestroyer(53, 7))
        /* Rebels. */
        .ship(createExplorer(8382, 299796))
        .ship(createXWing(843738, 299796, 8383))
        .ship(createXWing(843738, 299796, 8383))
        .ship(createXWing(843738, 299796, 8383))
        /* Dead. */
        .ship(createXWing(0, 299796, 8383))
        .ship(createTIEFighter(0, 72))
        .build();

    for (auto tries = 0; tries < 500; tries++) {
        BOOST_CHECK_EQUAL(battle.countRebelFleet(), 4);
        BOOST_CHECK_EQUAL(battle.countImperialFleet(), 4);

        BOOST_CHECK_COUT(battle.tick(5), "");

        BOOST_CHECK_EQUAL(battle.countRebelFleet(), 4);
        BOOST_CHECK_EQUAL(battle.countImperialFleet(), 4);

        BOOST_CHECK_COUT(battle.tick(10), "");
    }
}

BOOST_AUTO_TEST_CASE(zeroAttackBattle) {
    auto battle = SpaceBattle::Builder()
        .startTime(0)
        .maxTime(99)
        /* Imperials. */
        .ship(createDeathStar(100, 0))
        .ship(createTIEFighter(53, 0))
        .ship(createTIEFighter(53, 0))
        .ship(createImperialDestroyer(53, 0))
        /* Rebels. */
        .ship(createExplorer(8382, 299796))
        .ship(createXWing(843738, 299796, 0))
        .ship(createXWing(843738, 299796, 0))
        .ship(createXWing(843738, 299796, 0))
        /* Dead. */
        .ship(createXWing(0, 299796, 8383))
        .ship(createTIEFighter(0, 72))
        .build();

    for (auto tries = 0; tries < 1000; tries++) {
        BOOST_CHECK_EQUAL(battle.countRebelFleet(), 4);
        BOOST_CHECK_EQUAL(battle.countImperialFleet(), 4);

        auto tick = tries % 8 + 1;
        BOOST_CHECK_COUT(battle.tick(tick), "");
    }
}

BOOST_AUTO_TEST_CASE(oneAttackBattle) {
    auto battle = SpaceBattle::Builder()
        .startTime(2)
        .maxTime(99)
        /* Imperials. */
        .ship(createDeathStar(100, 1))
        /* Rebels. */
        .ship(createExplorer(100, 299796))
        .build();

    for (auto tries = 0; tries < 100; tries++) {
        BOOST_CHECK_EQUAL(battle.countRebelFleet(), 1);
        BOOST_CHECK_EQUAL(battle.countImperialFleet(), 1);

        BOOST_CHECK_COUT(battle.tick(100), "");
    }

    BOOST_CHECK_EQUAL(battle.countRebelFleet(), 0);
    BOOST_CHECK_EQUAL(battle.countImperialFleet(), 1);

    BOOST_CHECK_COUT(battle.tick(100), "IMPERIUM WON\n");
}

BOOST_AUTO_TEST_CASE(oneAttackBattleDraw) {
    auto battle = SpaceBattle::Builder()
        .startTime(2)
        .maxTime(99)
        /* Imperials. */
        .ship(createDeathStar(100, 1))
        /* Rebels. */
        .ship(createXWing(100, 299796, 1))
        .build();

    for (auto tries = 0; tries < 100; tries++) {
        BOOST_CHECK_EQUAL(battle.countRebelFleet(), 1);
        BOOST_CHECK_EQUAL(battle.countImperialFleet(), 1);

        BOOST_CHECK_COUT(battle.tick(100), "");
    }

    BOOST_CHECK_EQUAL(battle.countRebelFleet(), 0);
    BOOST_CHECK_EQUAL(battle.countImperialFleet(), 0);

    BOOST_CHECK_COUT(battle.tick(100), "DRAW\n");
}

BOOST_AUTO_TEST_CASE(oneAttackBattleRebel) {
    auto battle = SpaceBattle::Builder()
        .startTime(2)
        .maxTime(99)
        /* Imperials. */
        .ship(createDeathStar(100, 0))
        /* Rebels. */
        .ship(createXWing(100, 299796, 1))
        .build();

    for (auto tries = 0; tries < 100; tries++) {
        BOOST_CHECK_EQUAL(battle.countRebelFleet(), 1);
        BOOST_CHECK_EQUAL(battle.countImperialFleet(), 1);

        BOOST_CHECK_COUT(battle.tick(100), "");
    }

    BOOST_CHECK_EQUAL(battle.countRebelFleet(), 1);
    BOOST_CHECK_EQUAL(battle.countImperialFleet(), 0);

    BOOST_CHECK_COUT(battle.tick(100), "REBELLION WON\n");
}