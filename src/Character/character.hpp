#pragma once

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <map>
#include <array>
#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Character/weapons.hpp"
#include "Character/armor.hpp"

namespace dnd {
    class character {
    public:
        character(std::string initname,
                  std::string initclass,
                  std::string initrace,
                  std::string initbg,
                  int level = 1,
                  int strength = 10,
                  int dexterity = 10,
                  int constitution = 10,
                  int intelligence = 10,
                  int wisdom = 10,
                  int charisma = 10,
                  bool isNPC = false) {
            /**
             * Creates the character with basic attributes and stats in an easy constructor
             *
             * Very basic and does not include equipment or spells, nor does it return anything
             *
             * @param initname The name of the character
             * @param initclass The class of the character
             * @param initrace The race of the character
             * @param initbg The background of the character
             *
             * @param level The character level
             *
             * @param strength The character's strength (Default 10)
             * @param dexterity The character's dexterity (Defult 10)
             * @param constitution The character's constitution (Default 10)
             * @param intelligence The character's intelligence (Default 10)
             * @param wisdom The character's wisdom (Default 10)
             * @param charisma The character's charisma (Default 10)
             *
             * @param isNPC Demarcates whether this is an NPC or PC
             */

            cname = std::move(initname);
            cclass = std::move(initclass);
            crace = std::move(initrace);
            cbg = std::move(initbg);

            abilities = {{"STR", {strength, static_cast<int>((std::floor(strength/2) - 5))}},
                         {"DEX", {dexterity, static_cast<int>((std::floor(dexterity/2) - 5))}},
                         {"CON", {constitution, static_cast<int>((std::floor(constitution/2) - 5))}},
                         {"INT", {intelligence, static_cast<int>((std::floor(intelligence/2) - 5))}},
                         {"WIS", {wisdom, static_cast<int>((std::floor(wisdom/2) - 5))}},
                         {"CHA", {charisma, static_cast<int>(std::floor(charisma/2) - 5)}}};

            weapon = "FISTS";
        }

        ~character() = default;

        std::map<std::string, std::array<int, 2> > getAbilities() {
            /**
             * Returns the ability map
             *
             * Used so the base variables stay private
             *
             * @return The ability map
             */

            return abilities;
        }

        std::string getName() {
            /**
             * Returns the name of the character
             *
             * Used so the base variables stay private
             *
             * @return The character's name
             */

            return cname;
        }

        std::string getClass() {
            /**
             * Returns the class of the character
             *
             * Used so the base variables stay private
             *
             * @return The character's class
             */

            return cclass;
        }

        std::string getRace(){
            /**
             * Returns the race of the character
             *
             * Used so the base variables stay private
             *
             * @return The character's race
             */

            return crace;
        }

        std::string getBg(){
            /**
             * Returns the race of the character
             *
             * Used so the base variables stay private
             *
             * @return The character's background
             */

            return cbg;
        }

        int getAC() {
            /**
             * Returns the armor class
             *
             * @return The character's AC
             */

            return ac;
        }

        void setWeapon(std::string inWeapon){
            /**
             * Sets the weapon and updates equipment
             */

            equipment[0] = std::move(inWeapon);
        }

        void setArmor(std::string inArmor) {
            /**
             * Sets the armor and updates equipment
             */

            auto arm = armor::getArmor(inArmor);

            ac = arm.baseAC;

            if (abilities["DEX"][1] >= arm.dexMax) {
                ac += arm.dexMax;
            } else {
                ac += abilities["DEX"][1];
            }

            equipment[1] = std::move(inArmor);
        }

        void setAC(int a) {
            ac = a;
        }

        void refreshAC() {
            /**
             * Refreshes the ac
             *
             * Required if a shield is added or removed
             */

            auto arm = armor::getArmor(equipment[1]);

            ac = arm.baseAC;

            if (abilities["DEX"][1] >= arm.dexMax) {
                ac += arm.dexMax;
            } else {
                ac += abilities["DEX"][1];
            }

            if(std::count(equipment.begin(), equipment.end(), "SHIELD")) {
                ac += 2;
            }
        }

        std::string getWeapon() {
            /**
             * Gets the weapon name
             *
             * @return The weapon name
             */

            return equipment[0];
        }

        std::string getArmor() {
            /**
             * Gets the armor name
             *
             * @return The armor name
             */

            return equipment[1];
        }

        int attack() {
            weapons::Weapons weap = weapons::getWeapon(equipment[0]);

            int att = weap.ability;
            int abi = (att == 1)?abilities["DEX"][1]:(att == 2)?abilities["STR"][1]:(att == 3)?(abilities["DEX"][1]>=abilities["STR"][1])?abilities["DEX"][1]:abilities["STR"][1]:0;

            int dmg = abi;

            for (int i = 0; i < weap.numberDice; ++i) {
                dmg += weap.die.roll();
            }

            return dmg;
        }

        void damage(unsigned int dmg) {
            /**
             * Alters character hp negatively
             */

            hp -= dmg;
        }

        void heal(unsigned int heal) {
            /**
             * Alters character hp positively
             */

            hp += heal;

            if (hp > maxHP) {
                hp = maxHP;
            }
        }

    private:
        static bool npc;

        std::string weapon;
        std::string cname, cclass, crace, cbg;
        std::map<std::string, std::array<int, 2> > abilities;

        int hp = 0;
        int maxHP = 0;
        int ac = abilities["DEX"][1] + 10;
        int gp;

        std::vector<std::string> equipment = {"FISTS", "UNARMORED"}; ///Equipped items
        std::vector<std::string> misc = {}; ///Other items
        std::vector<std::string> proficiencies {"Common"};

        ///0 = None, 1 = Acid, 2 = Bludgeoning, 3 = Cold, 4 = Fire, 5 = Force, 6 = Lightning, 7 = Necrotic, 8 = Piercing, 9 = Poison, 10 = Psychic, 11 = Radiant, 12 = Slashing, 13 = Thunder
        std::vector<int> vulnerabilities = {0};
        std::vector<int> immunities = {0};
        std::vector<int> resistances = {0};
    };
}

#endif /* CHARACTER_HPP */