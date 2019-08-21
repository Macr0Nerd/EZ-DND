#define CATCH_CONFIG_MAIN

#include <iostream>
#include "catch.hpp"
#include "Core/board.hpp"

TEST_CASE("Dice can roll within a range", "[dice]") {
    SECTION("Default Dice") {
        int x;

        SECTION("d0") {
            INFO("d0 Test Start");
            std::clog << "Starting d0 Tests..." << std::endl;

            x = dnd::d0.roll();
            REQUIRE(x == 0);

            std::cout << "Passed d0" << std::endl;
        }

        SECTION("d1") {
            INFO("d1 Test Start");
            std::clog << "Starting d1 Tests..." << std::endl;

            x = dnd::d1.roll();
            REQUIRE(x == 1);

            std::cout << "Passed d1" << std::endl;
        }

        SECTION("d2") {
            INFO("d2 Test Start");
            std::clog << "Starting d2 Tests..." << std::endl;

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d2 test " << i) {
                    INFO("d2 Test " + std::to_string(i) + " Start");

                    x = dnd::d2.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 2);
                }
            }

            std::cout << "Passed d2" << std::endl;
        }

        SECTION("d4") {
            INFO("d4 Test Start");
            std::clog << "Starting d4 Tests..." << std::endl;

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d4 test " << i) {
                    INFO("d4 Test " + std::to_string(i) + " Start");

                    x = dnd::d4.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 4);
                }
            }

            std::cout << "Passed d4" << std::endl;
        }

        SECTION("d6") {
            INFO("d6 Test Start");
            std::clog << "Starting d6 Tests..." << std::endl;

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d6 test " << i) {
                    INFO("d6 Test " + std::to_string(i) + " Start");

                    x = dnd::d6.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 6);
                }
            }

            std::cout << "Passed d6" << std::endl;
        }

        SECTION("d8") {
            INFO("d8 Test Start");
            std::clog << "Starting d8 Tests..." << std::endl;

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d8 test" << i) {
                    INFO("d8 Test " + std::to_string(i) + " Start");

                    x = dnd::d8.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 8);
                }
            }

            std::cout << "Passed d8" << std::endl;
        }

        SECTION("d10") {
            INFO("d10 Test Start");
            std::clog << "Starting d10 Tests..." << std::endl;

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d10 test" << i) {
                    INFO("d10 Test " + std::to_string(i) + " Start");

                    x = dnd::d10.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 10);
                }
            }

            std::cout << "Passed d10" << std::endl;
        }

        SECTION("d12") {
            INFO("d12 Test Start");
            std::clog << "Starting d12 Tests..." << std::endl;

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d12 test" << i) {
                    INFO("d12 Test " + std::to_string(i) + " Start");

                    x = dnd::d12.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 12);
                }
            }

            std::cout << "Passed d12" << std::endl;
        }

        SECTION("d20") {
            INFO("d20 Test Start");
            std::clog << "Starting d20 Tests..." << std::endl;

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d20 test" << i) {
                    INFO("d20 Test " + std::to_string(i) + " Start");

                    x = dnd::d20.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 20);
                }
            }

            std::cout << "Passed d20" << std::endl;
        }

        SECTION("d100") {
            INFO("d100 Test Start");
            std::clog << "Starting d100 Tests..." << std::endl;

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("d100 test" << i) {
                    INFO("d100 Test " + std::to_string(i) + " Start");

                    x = dnd::d100.roll();
                    CHECK(x >= 1);
                    CHECK(x <= 100);
                }
            }

            std::cout << "Passed d100" << std::endl;
        }

        std::cout << "Passed Default Dice" << std::endl;
    }

    SECTION("Custom dice") {
        dnd::core::dice die = dnd::core::dice();

        SECTION("Default Case") {
            INFO("Default Test Start");
            std::clog << "Starting default case Tests..." << std::endl;

            REQUIRE(die.roll() == -1);

            std::cout << "Passed default case" << std::endl;
        }

        SECTION("Custom Case") {
            int x;

            INFO("Custom Case Start");
            std::clog << "Starting custom case Tests..." << std::endl;

            die = dnd::core::dice(50);

            for (int i = 0; i < 5; ++i) {
                DYNAMIC_SECTION("Custom Test " << i) {
                    INFO("Custom Test " + std::to_string(i) + " Start");

                    x = die.roll();

                    CHECK(x >= 1);
                    CHECK(x <= 50);
                }
            }

            std::cout << "Passed Custom Case" << std::endl;
        }

        SECTION("Non-Natural Case") {
            die = dnd::core::dice(-10);

            INFO("Non-natural Test Start");
            std::clog << "Starting non-natural case Tests..." << std::endl;

            CHECK(die.roll() == -10);

            std::cout << "Passed non-natural case" << std::endl;
        }

        std::cout << "Passed Custom Dice" << std::endl;
    }
}

TEST_CASE("Weapons data is accessible", "[weapons]") {
    SECTION("Dice check") {
        INFO("Dice tests starting");
        std::clog << "Starting weapons/dice Tests..." << std::endl;

        CHECK(dnd::weapons::getWeapon("DAGGER").die == dnd::d4);
        CHECK(dnd::weapons::getWeapon("SHORTBOW").die == dnd::d6);
        CHECK(dnd::weapons::getWeapon("LONGSWORD+").die == dnd::d10);
        CHECK(dnd::weapons::getWeapon("LONGBOW").die == dnd::d8);

        std::cout << "Passed dice tests" << std::endl;
    }

    SECTION("Ability check") {
        INFO("Ability tests starting");
        std::clog << "Starting weapons/ability Tests..." << std::endl;

        CHECK(dnd::weapons::getWeapon("DAGGER").ability == 3);
        CHECK(dnd::weapons::getWeapon("SHORTBOW").ability == 2);
        CHECK(dnd::weapons::getWeapon("LONGSWORD+").ability == 1);
        CHECK(dnd::weapons::getWeapon("LONGBOW").ability == 2);

        std::cout << "Passed ability tests" << std::endl;
    }

    SECTION("Martial Check") {
        INFO("Martial tests starting");
        std::clog << "Starting weapons/martial Tests..." << std::endl;

        CHECK_FALSE(dnd::weapons::getWeapon("DAGGER").martial);
        CHECK_FALSE(dnd::weapons::getWeapon("SHORTBOW").martial);
        CHECK(dnd::weapons::getWeapon("LONGSWORD+").martial);
        CHECK(dnd::weapons::getWeapon("LONGBOW").martial);

        std::cout << "Passed martial tests" << std::endl;
    }

    SECTION("Range Check") {
        INFO("Range tests starting");
        std::clog << "Starting weapons/range Tests..." << std::endl;

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

        std::cout << "Passed range tests" << std::endl;
    }
}

TEST_CASE("Armor data is accessible", "[armor]") {
    SECTION("Base AC") {
        INFO("Base AC Tests");
        std::clog << "Starting armor/ac Tests..." << std::endl;

        CHECK(dnd::armor::getArmor("LEATHER").baseAC == 11);
        CHECK(dnd::armor::getArmor("BREASTPLATE").baseAC == 14);
        CHECK(dnd::armor::getArmor("PLATE").baseAC == 18);

        std::cout << "Passed base AC" << std::endl;
    }

    SECTION("Armor type") {
        INFO("Armor Type Tests");
        std::clog << "Starting armor/type Tests..." << std::endl;

        CHECK(dnd::armor::getArmor("LEATHER").armType == 'L');
        CHECK(dnd::armor::getArmor("BREASTPLATE").armType == 'M');
        CHECK(dnd::armor::getArmor("PLATE").armType == 'H');

        std::cout << "Passed armor type" << std::endl;
    }

    SECTION("Stealth") {
        INFO("Stealth Tests");
        std::clog << "Starting armor/stealth Tests..." << std::endl;

        CHECK_FALSE(dnd::armor::getArmor("LEATHER").disadvantage);
        CHECK_FALSE(dnd::armor::getArmor("BREASTPLATE").disadvantage);
        CHECK(dnd::armor::getArmor("PLATE").disadvantage);

        std::cout << "Passes stealth tests" << std::endl;
    }
}

TEST_CASE("The board's functions work", "[board]") {
    dnd::character fred = dnd::character("Fred", "PALADIN", "HILL DWARF", "ACOLYTE", 1, 14, 12, 15, 8, 13, 10, false);
    fred.setWeapon("GREATSWORD");
    fred.setArmor("PLATE");

    dnd::character bob = dnd::character("Bob", "ROGUE", "LIGHTFOOT HALFLING", "ACOLYTE", 1, 10, 14, 15, 12, 8, 13);
    bob.setWeapon("RAPIER");
    bob.setArmor("STUDDED LEATHER");

    dnd::core::board board = dnd::core::board(15);

    board.place(fred, 6, 6);
    board.place(bob, 7, 6);
    
    SECTION("Adjacent Test") {
        INFO("Starting adjacent test");
        std::clog << "Starting adjacent tests..." << std::endl;
        
        CHECK(board.getAdjacent(fred)[0].getName() == "Bob");
        
        std::cout << "Passed adjacent test" << std::endl;
    }
    
    SECTION("Move Test") {
        INFO("Starting move test");
        std::clog << "Starting adjacent tests..." << std::endl;
        
        CHECK(board.getPos(bob).first == 7);
        
        board.move(bob, 5, 6);
        
        CHECK(board.getPos(bob).first == 5);
        
        std::cout << "Passed move test" << std::endl;
    }
}