#pragma once

#include <string>
#include <map>
#include "../Core/dice.hpp"

namespace dnd {
    class weapons {
    public:
        weapons(){
            /**
             * Used to construct the weapons class
             *
             * Doesn't do much in terms or parameters or return values
             */

            weaps = {
                    {"CLUB", d4},
                    {"DAGGER", d4},
                    {"GREATCLUB", d8},
                    {"HANDAXE", d6},
                    {"JAVELIN", d6},
                    {"LIGHT HAMMER", d4},
                    {"MACE", d6},
                    {"QUARTERSTAFF", d6},
                    {"QUARTERSTAFF+", d8},
                    {"SICKLE", d4},
                    {"SPEAR", d6},
                    {"SPEAR+", d8},
                    {"CROSSBOW", d8},
                    {"DART", d4},
                    {"SHORTBOW", d6},
                    {"SLING", d4},
                    {"BATTLEAXE", d8},
                    {"BATTLEAXE+", d10},
                    {"FLAIL", d8},
                    {"GLAIVE", d10},
                    {"GREATAXE", d12},
                    {"HALBERD", d10},
                    {"LANCE", d12},
                    {"LONGSWORD", d8},
                    {"LONGSWORD+", d10},
                    {"MAUL", d6},
                    {"MORNINGSTAR", d8},
                    {"PIKE", d10},
                    {"RAPIER", d8},
                    {"SCIMITAR", d6},
                    {"SHORTSWORD", d6},
                    {"TRIDENT", d6},
                    {"TRIDENT+", d8},
                    {"WAR PICK", d8},
                    {"WARHAMMER", d8},
                    {"WARHAMMER+", d10},
                    {"WHIP", d4},
                    {"BLOWGUN", d1},
                    {"HAND CROSSBOW", d6},
                    {"HEAVY CROSSBOW", d10},
                    {"LONGBOW", d8},
                    {"NET", d0}
            };

            info = {
                    {"CLUB", {1, 2, 2, 0, 0}},
                    {"DAGGER", {1, 3, 8, 0, 2}},
                    {"GREATCLUB", {1, 2, 2, 0, 0}},
                    {"HANDAXE", {1, 2, 12, 0, 2}},
                    {"JAVELIN", {1, 2, 8, 0, 2}},
                    {"LIGHT HAMMER", {1, 2, 2, 0, 2}},
                    {"MACE", {1, 2, 2, 0, 0}},
                    {"QUARTERSTAFF", {1, 2, 2, 0, 0}},
                    {"QUARTERSTAFF+", {1, 2, 2, 0, 0}},
                    {"SICKLE", {1, 2, 12, 0, 0}},
                    {"SPEAR", {1, 2, 8, 0, 2}},
                    {"SPEAR+", {1, 2, 8, 0, 0}},
                    {"LIGHT CROSSBOW", {1, 1, 8, 0, 1}},
                    {"DART", {1, 1, 8, 0, 3}},
                    {"SHORTBOW", {1, 1, 8, 0, 1}},
                    {"SLING", {1, 1, 2, 0, 1}},
                    {"BATTLEAXE", {1, 2, 12, 1, 0}},
                    {"BATTLEAXE+", {1, 2, 12, 1, 0}},
                    {"FLAIL", {1, 2, 2, 1, 0}},
                    {"GLAIVE", {1, 2, 12, 1, 4}},
                    {"GREATAXE", {1, 2, 12, 1, 0}},
                    {"HALBERD", {2, 2, 12, 1, 0}},
                    {"LANCE", {1, 2, 8, 1, 4}},
                    {"LONGSWORD", {1, 2, 12, 1, 0}},
                    {"LONGSWORD+", {1, 2, 12, 1, 0}},
                    {"MAUL", {2, 2, 2, 1, 0}},
                    {"MORNINGSTAR", {1, 2, 8, 1, 0}},
                    {"PIKE", {1, 2, 8, 1, 4}},
                    {"RAPIER", {1, 3, 8, 1, 0}},
                    {"SCIMITAR", {1, 3, 12, 1, 0}},
                    {"SHORTSWORD", {1, 3, 8, 1, 0}},
                    {"TRIDENT", {1, 3, 8, 1, 2}},
                    {"TRIDENT+", {1, 3, 8, 1, 2}},
                    {"WAR PICK", {1, 2, 8, 1, 0}},
                    {"WARHAMMER", {1, 2, 2, 1, 0}},
                    {"WARHAMMER+", {1, 2, 2, 1, 0}},
                    {"WHIP", {1, 3, 2, 1, 4}},
                    {"BLOWGUN", {1, 1, 8, 1, 1}},
                    {"HAND CROSSBOW", {1, 1, 8, 1, 1}},
                    {"HEAVY CROSSBOW", {1, 1, 8, 1, 1}},
                    {"LONGBOW", {1, 1, 8, 1, 1}},
                    {"NET", {1, 1, 0, 1, 2}}
            };
        }

        ~weapons() = default;

        dnd::core::dice getWeaponDice(std::string name){
            /**
             * Returns the dice used for the specified weapon
             *
             * @param name Weapon's name
             *
             * @return Weapon's die
             */

            return weaps.at(name);
        }

        std::array<int, 5> getWeaponInfo(std::string name) {
            /**
             * Returns the other info about the weapon
             *
             * @param name Weapon's name
             *
             * @return Weapon's info
             */

            return info.at(name);
        }

    private:
        ///Used to keep track of all the weapons with name & dice type
        std::map<std::string, core::dice> weaps;

        ///Used to keep track of all the weapons with names & further info
        ///Ints are dice number, ability type, damage type, martial/simple, and range

        ///1 = Dexterity, 2 = Strength, 3 = Finesse

        ///0 = None, 1 = Acid, 2 = Bludgeoning, 3 = Cold, 4 = Fire, 5 = Force,
        ///6 = Lightning, 7 = Necrotic, 8 = Piercing, 9 = Poison, 10 = Psychic,
        ///11 = Radiant, 12 = Slashing, 13 = Thunder

        ///0 = Simple, 1 = Martial

        ///0 = Melee, 1 = Ranged, 2 = Thrown, 3 = Ranged/Thrown, 4 = Reach
        std::map<std::string, std::array<int, 5>> info;
    };
}