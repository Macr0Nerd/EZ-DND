#pragma once

#include <string>
#include <map>
#include <vector>
#include "../Core/dice.hpp"

namespace dnd {
    class weapons {
    public:
        struct Weapons {
            std::string name;
            core::dice die;
            short numberDice;
            short ability; ///1 = Strength, 2 = Dexterity, 3 = Finesse
            short damageType; ///0 = None, 1 = Acid, 2 = Bludgeoning, 3 = Cold, 4 = Fire, 5 = Force, 6 = Lightning, 7 = Necrotic, 8 = Piercing, 9 = Poison, 10 = Psychic, 11 = Radiant, 12 = Slashing, 13 = Thunder
            bool martial;
            int ranged; ///0 = Melee, 1 = Ranged, 2 = Thrown, 3 = Ranged/Thrown, 4 = Reach
            std::pair<int, int> range;
        };

        weapons() = default;
        ~weapons() = default;

        static Weapons getWeapon (std::string name){
            return A::create_map().at(name);
        }

    private:
        struct A {
            static std::map<std::string, Weapons> create_map() {
                /**
                 * Returns the weapons list
                 *
                 * Map parameters are the Weapons struct
                 *
                 * @return The weapons list (static)
                 */

                std::map<std::string, Weapons> m;

                ///Simple Martial Weapons
                m["FISTS"] = {"FISTS", d1, 1, 1, 2, false, 0, {0, 0}};
                m["CLUB"] = {"CLUB", d4, 1, 1, 2, false, 0, {0, 0}};
                m["DAGGER"] = {"DAGGER", d4, 1, 3, 8, false, 2, {20, 60}};
                m["GREATCLUB"] = {"GREATCLUB", d8, 1, 1, 2, false, 0, {0, 0}};
                m["HANDAXE"] = {"HANDAXE", d6, 1, 1, 12, false, 2, {20, 60}};
                m["JAVELIN"] = {"JAVELIN", d6, 1, 1, 8, false, 2, {30, 120}};
                m["LIGHT HAMMER"] = {"LIGHT HAMMER", d4, 1, 1, 2, false, 2, {20, 60}};
                m["MACE"] = {"MACE", d6, 1, 1, 2, false, 0, {0, 0}};
                m["QUARTERSTAFF"] = {"QUARTERSTAFF", d6, 1, 1, 2, false, 0, {0, 0}};
                m["QUARTERSTAFF+"] = {"QUARTERSTAFF+", d8, 1, 1, 2, false, 0, {0, 0}};
                m["SICKLE"] = {"SICKLE", d4, 1, 1, 12, false, 0, {0, 0}};
                m["SPEAR"] = {"SPEAR", d6, 1, 1, 8, false, 2, {20, 60}};
                m["SPEAR+"] = {"SPEAR+", d8, 1, 1, 8, false, 2, {20, 60}};

                ///Simple Ranged Weapons
                m["LIGHT CROSSBOW"] = {"LIGHT CROSSBOW", d8, 1, 2, 8, false, 2, {80, 320}};
                m["DART"] = {"DART", d4, 1, 3, 8, false, 3, {20, 60}};
                m["SHORTBOW"] = {"SHORTBOW", d6, 1, 2, 8, false, 2, {80, 320}};
                m["SLING"] = {"SLING", d4, 1, 2, 2, false, 2, {30, 120}};

                ///Martial Melee Weapons
                m["BATTLEAXE"] = {"BATLLEAXE", d8, 1, 1, 12, true, 0, {0, 0}};
                m["BATTLEAXE+"] = {"BATTLEAXE+", d10, 1, 1, 12, true, 0, {0, 0}};
                m["FLAIL"] = {"FLAIL", d8, 1, 1, 2, true, 0, {0, 0}};
                m["GLAIVE"] = {"GLAIVE", d10, 1, 1, 12, true, 4, {0, 0}};
                m["GREATAXE"] = {"GREATAXE", d12, 1, 1, 12, true, 0, {0, 0}};
                m["GREATSWORD"] = {"GREATSWORD", d6, 2, 1, 12, true, 0, {0, 0}};
                m["HALBERD"] = {"HALBERD", d10, 1, 1, 12, true, 4, {0, 0}};
                m["LANCE"] = {"LANCE", d12, 1, 1, 8, true, 4, {0, 0}};
                m["LONGSWORD"] = {"LONGSWORD", d8, 1, 1, 12, true, 0, {0, 0}};
                m["LONGSWORD+"] = {"LONGSWORD+", d10, 1, 1, 12, true, 0, {0, 0}};
                m["MAUL"] = {"MAUL", d6, 2, 1, 2, true, 0, {0, 0}};
                m["MORNINGSTAR"] = {"MORNINGSTAR", d8, 1, 1, 8, true, 0, {0, 0}};
                m["PIKE"] = {"PIKE", d6, 1, 1, 8, true, 4, {0, 0}};
                m["RAPIER"] = {"RAPIER", d6, 1, 3, 8, true, 0, {0, 0}};
                m["SCIMITAR"] = {"SCIMITAR", d6, 1, 3, 8, true, 0, {0, 0}};
                m["SHORTSWORD"] = {"SHORTSWORD", d4, 1, 3, 8, true, 0, {0, 0}};
                m["TRIDENT"] = {"TRIDENT", d6, 1, 1, 8, true, 2, {20, 60}};
                m["TRIDENT+"] = {"TRIDENT+", d8, 1, 1, 8, true, 2, {20, 60}};
                m["WAR PICK"] = {"WAR PICK", d8, 1, 1, 8, true, 0, {0, 0}};
                m["WARHAMMER"] = {"WARHAMMER", d8, 1, 1, 2, true, 0, {0, 0}};
                m["WARHAMMER+"] = {"WARHAMMER+", d10, 1, 1, 2, true, 0, {0, 0}};
                m["WHIP"] = {"WHIP", d4, 1, 3, 12, true, 4, {0, 0}};

                ///Martial Ranged Weapons
                m["BLOWGUN"] = {"BLOWGUN", d1, 1, 2, 8, true, 1, {25, 100}};
                m["HAND CROSSBOW"] = {"HAND CROSSBOW", d6, 1, 2, 8, true, 1, {30, 120}};
                m["HEAVY CROSSBOW"] = {"HEAVY CROSSBOW", d10, 1, 2, 8, true, 1, {100, 400}};
                m["LONGBOW"] = {"LONGBOW", d8, 1, 2, 8, true, 1, {150, 600}};
                m["NET"] = {"NET", d0, 1, 2, 0, true, 2, {5, 15}};

                return m;
            };
        };
    };
}