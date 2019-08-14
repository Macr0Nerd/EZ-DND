#pragma once

#import <string>
#import <map>

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

            cname = initname;
            cclass = initclass;
            crace = initrace;
            cbg = initbg;

            abilities = {{"STR", strength},
                         {"DEX", dexterity},
                         {"CON", constitution},
                         {"INT", intelligence},
                         {"WIS", wisdom},
                         {"CHA", charisma}};
        }

        std::map<std::string, int> getAbilities() {
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


    private:
        bool npc = false;

        std::string cname, cclass, crace, cbg;
        std::map<std::string, int> abilities;
    };
}