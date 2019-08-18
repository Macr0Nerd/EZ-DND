#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Core/dice.hpp"
#include "Character/weapons.hpp"

TEST_CASE("Dice can roll within a range", "[dice]") {
    SECTION("Default Dice") {
        int x;

        SECTION("d0") {
            INFO("d0 Test Start");

            x = dnd::d0.roll();
            REQUIRE(x == 0);

            SUCCEED("Passed d0");
        }

        SECTION("d1") {
            INFO("d1 Test Start");

            x = dnd::d1.roll();
            REQUIRE(x == 1);

            SUCCEED("Passed d1");
        }

        SECTION("d2") {
            INFO("d2 Test Start");

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d2 test " << i) {
                    INFO("d2 Test " + std::to_string(i) + " Start");

                    x = dnd::d2.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 2);
                }
            }

            SUCCEED("Passed d2");
        }

        SECTION("d4") {
            INFO("d4 Test Start");

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d4 test " << i) {
                    INFO("d4 Test " + std::to_string(i) + " Start");

                    x = dnd::d4.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 4);
                }
            }

            SUCCEED("Passed d4");
        }

        SECTION("d6") {
            INFO("d6 Test Start");

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d6 test " << i) {
                    INFO("d6 Test " + std::to_string(i) + " Start");

                    x = dnd::d6.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 6);
                }
            }

            SUCCEED("Passed d6");
        }

        SECTION("d8") {
            INFO("d8 Test Start");

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d8 test" << i) {
                    INFO("d8 Test " + std::to_string(i) + " Start");

                    x = dnd::d8.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 8);
                }
            }

            SUCCEED("Passed d8");
        }

        SECTION("d10") {
            INFO("d10 Test Start");

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d10 test" << i) {
                    INFO("d10 Test " + std::to_string(i) + " Start");

                    x = dnd::d10.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 10);
                }
            }

            SUCCEED("Passed d10");
        }

        SECTION("d12") {
            INFO("d12 Test Start");

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d12 test" << i) {
                    INFO("d12 Test " + std::to_string(i) + " Start");

                    x = dnd::d12.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 12);
                }
            }

            SUCCEED("Passed d12");
        }

        SECTION("d20") {
            INFO("d20 Test Start");

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d20 test" << i) {
                    INFO("d20 Test " + std::to_string(i) + " Start");

                    x = dnd::d20.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 20);
                }
            }

            SUCCEED("Passed d20");
        }

        SECTION("d100") {
            INFO("d100 Test Start");

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d100 test" << i) {
                    INFO("d100 Test " + std::to_string(i) + " Start");

                    x = dnd::d100.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 100);
                }
            }

            SUCCEED("Passed d100");
        }

        SUCCEED("Passed Default Dice");
    }

    SECTION("Custom dice") {
        dnd::core::dice die = dnd::core::dice();

        SECTION("Default Case") {
            INFO("Default Test Start");

            REQUIRE(die.roll() == -1);

            SUCCEED("Passed default case");
        }

        SECTION("Custom Case") {
            int x;

            INFO("Custom Case Start");

            die = dnd::core::dice(50);

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("Custom Test " << i) {
                    INFO("Custom Test " + std::to_string(i) + " Start");

                    x = die.roll();

                    CHECK(x >= 1);
                    CHECK(x <= 50);
                }
            }

            SUCCEED("Passed Custom Case");
        }

        SECTION("Non-Natural Case") {
            die = dnd::core::dice(-10);

            INFO("Non-natural Test Start");

            CHECK(die.roll() == -10);

            SUCCEED("Passed non-natural case");
        }

        SUCCEED("Passed Custom Dice");
    }
}

TEST_CASE("Weapons data is accessible", "[weapons]") {
    SECTION("Dice check") {
        INFO("Dice tests starting");

        CHECK(dnd::weapons::getWeapon("DAGGER").die == dnd::d4);
        CHECK(dnd::weapons::getWeapon("SHORTBOW").die == dnd::d6);
        CHECK(dnd::weapons::getWeapon("LONGSWORD+").die == dnd::d10);
        CHECK(dnd::weapons::getWeapon("LONGBOW").die == dnd::d8);

        SUCCEED("Passed dice tests");
    }

    SECTION("Ability check") {
        INFO("Ability tests starting");

        CHECK(dnd::weapons::getWeapon("DAGGER").ability == 3);
        CHECK(dnd::weapons::getWeapon("SHORTBOW").ability == 2);
        CHECK(dnd::weapons::getWeapon("LONGSWORD+").ability == 1);
        CHECK(dnd::weapons::getWeapon("LONGBOW").ability == 2);

        SUCCEED("Passed ability tests");
    }

    SECTION("Martial Check") {
        INFO("Martial tests starting");

        CHECK_FALSE(dnd::weapons::getWeapon("DAGGER").martial);
        CHECK_FALSE(dnd::weapons::getWeapon("SHORTBOW").martial);
        CHECK(dnd::weapons::getWeapon("LONGSWORD+").martial);
        CHECK(dnd::weapons::getWeapon("LONGBOW").martial);

        SUCCEED("Passed martial tests");
    }

    SECTION("Range Check") {
        INFO("Range tests starting");

        CHECK(dnd::weapons::getWeapon("DAGGER").ranged == 2);
        CHECK(dnd::weapons::getWeapon("DAGGER").range.first == 20);
        CHECK(dnd::weapons::getWeapon("DAGGER").range.second == 60);

        CHECK(dnd::weapons::getWeapon("SHORTBOW").ranged == 1);
        CHECK(dnd::weapons::getWeapon("SHORTBOW").range.first == 80);
        CHECK(dnd::weapons::getWeapon("SHORTBOW").range.second == 320);

        CHECK(dnd::weapons::getWeapon("GLAIVE").ranged == 4);
        CHECK(dnd::weapons::getWeapon("GLAIVE").range.first == 0);
        CHECK(dnd::weapons::getWeapon("GLAIVE").range.second == 0);

        CHECK(dnd::weapons::getWeapon("NET").ranged == 3);
        CHECK(dnd::weapons::getWeapon("NET").range.first == 5);
        CHECK(dnd::weapons::getWeapon("NET").range.second == 15);

        SUCCEED("Passed range tests");
    }
}