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
        class race {
        public:
            race() = default;
            ~race() = default;

            struct Race {
                std::string Name;
                std::vector<std::string> abis; ///Abilities to improve
                std::vector<unsigned short> boosts; ///How much to improve them by

                char size;

                unsigned int speed;

                std::map<std::string, std::string> traits;
                std::vector<std::string> prof;
            };

            static Race getRace(const std::string& name) {
                return A::createMap().at(name);
            }

        private:
            struct A {
                static std::map<std::string, Race> createMap() {
                    std::map<std::string, Race> m;

                    m["HILL DWARF"] = {"HILL DWARF", {"CON", "WIS", "HP"}, {2, 1, 1}, 'M', 25,
                                       {
                                            {"DARKVISION", "Accustomed to life underground, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray."},
                                            {"DWARVEN RESILIENCE", "You have advantage on saving throws against poison, and you have resistance against poison damage."},
                                            {"STONECUNNING", "Whenever you make an Intelligence (History) check related to the origin of stonework, you are considered proficient in the History skill and add double your proficiency bonus to the check, instead of your normal proficiency bonus."}},
                                       {"BATTLEAXE", "HANDAXE", "LIGHT HAMMER", "WARHAMMER", "SMITH'S TOOLS", "BREWER'S SUPPLIES", "MASON'S TOOLS"}};

                    m["HIGH ELF"] = {"HIGH ELF", {"DEX", "INT"}, {2, 1}, 'M', 30,
                                     {
                                            {"DARKVISION", "Accustomed to twilit forests and the night sky, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray."},
                                            {"FEY ANCESTRY", "You have advantage on saving throws against being charmed, and magic can’t put you to sleep."},
                                            {"TRANCE", "Elves don’t need to sleep. Instead, they meditate deeply, remaining semiconscious, for 4 hours a day. (The Common word for such meditation is “trance.”) While meditating, you can dream after a fashion; such dreams are actually mental exercises that have become reflexive through years of practice. After resting in this way, you gain the same benefit that a human does from 8 hours of sleep."}},
                                     {"PERCEPTION", "LONGSWORD", "SHORTSWORD", "SHORTBOW", "LONGBOW"}};

                    m["LIGHTFOOT HALFLING"] = {"LIGHTFOOT HALFLING", {"DEX", "CHA"}, {2, 1}, 'S', 25,
                                               {
                                                    {"LUCKY", "When you roll a 1 on the d20 for an attack roll, ability check, or saving throw, you can reroll the die and must use the new roll."},
                                                    {"BRAVE", "You have advantage on saving throws against being frightened."},
                                                    {"HALFLING NIMBLENESS", "You can move through the space of any creature that is of a size larger than yours."},
                                                    {"NATURALLY STEALTHY", "You can attempt to hide even when you are obscured only by a creature that is at least one size larger than you."}},
                                               {}};

                    m["HUMAN"] = {"HUMAN", {"STR", "DEX", "CON", "WIS", "INT", "CHA"}, {1, 1, 1, 1, 1, 1}, 'M', 30,
                                  {},
                                  {}};

                    m["DRAGONBORN"] = {"DRAGONBORN", {"STR", "CHA"}, {2, 1}, 'M', 30,
                                       {
                                            {"DRACONIC ANCESTRY", "You have draconic ancestry. Choose one type of dragon from the Draconic Ancestry table. Your breath weapon and damage resistance are determined by the dragon type, as shown in the table."},
                                            {"BREATH WEAPON", "You can use your action to exhale destructive energy. Your draconic ancestry determines the size, shape, and damage type of the exhalation. When you use your breath weapon, each creature in the area of the exhalation must make a saving throw, the type of which is determined by your draconic ancestry. The DC for this saving throw equals 8 + your Constitution modifier + your proficiency bonus. A creature takes 2d6 damage on a failed save, and half as much damage on a successful one. The damage increases to 3d6 at 6th level, 4d6 at 11th level, and 5d6 at 16th level. After you use your breath weapon, you can’t use it again until you complete a short or long rest."},
                                            {"DAMAGE RESISTANCE", "You have resistance to the damage type associated with your draconic ancestry."}},
                                       {}};

                    m["ROCK GNOME"] = {"ROCK GNOME", {"INT", "CON"}, {2, 1}, 'S', 25,
                                       {
                                            {"DARKVISION", "Accustomed to life underground, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray."},
                                            {"GNOME CUNNING", "You have advantage on all Intelligence, Wisdom, and Charisma saving throws against magic."},
                                            {"ARTIFICIER'S LORE", "Whenever you make an Intelligence (History) check related to magic items, alchemical objects, or technological devices, you can add twice your proficiency bonus, instead of any proficiency bonus you normally apply."},
                                            {"TINKER", "You have proficiency with artisan’s tools (tinker’s tools). Using those tools, you can spend 1 hour and 10 gp worth of materials to construct a Tiny clockwork device (AC 5, 1 hp). The device ceases to function after 24 hours (unless you spend 1 hour repairing it to keep the device functioning), or when you use your action to dismantle it; at that time, you can reclaim the materials used to create it. You can have up to three such devices active at a time. When you create a device, choose one of the following options:\n"
                                                       "Clockwork Toy. This toy is a clockwork animal, monster, or person, such as a frog, mouse, bird, dragon, or soldier. When placed on the ground, the toy moves 5 feet across the ground on each of your turns in a random direction. It makes noises as appropriate to the creature it represents.\n"
                                                       "Fire Starter. The device produces a miniature flame, which you can use to light a candle, torch, or campfire. Using the device requires your action.\n"
                                                       "Music Box. When opened, this music box plays a single song at a moderate volume. The box stops playing when it reaches the song’s end or when it is closed."}},
                                       {"ARTISAN's TOOLS"}};

                    m["HALF-ELF"] = {"HALF-ELF", {"CHA"}, {2}, 'M', 30,
                                     {
                                        {"ABILITY SCORE INCREASE", "Two ability scores of your choice increase by 1"},
                                        {"DARKVISION", "Thanks to your elf blood, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray."},
                                        {"FEY ANCESTRY", "You have advantage on saving throws against being charmed, and magic can’t put you to sleep."},
                                        {"SKILL VERSATILITY", "You gain proficiency in two skills of your choice."}},
                                     {}};

                    m["HALF-ORC"] = {"HALF-ORC", {"STR", "CON"}, {2, 1}, 'M', 30,
                                     {
                                        {"DARKVISION", "Thanks to your orc blood, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray."},
                                        {"RELENTLESS ENDURANCE", "When you are reduced to 0 hit points but not killed outright, you can drop to 1 hit point instead. You can’t use this feature again until you finish a long rest."},
                                        {"SAVAGE ATTACKS", "When you score a critical hit with a melee weapon attack, you can roll one of the weapon’s damage dice one additional time and add it to the extra damage of the critical hit."}},
                                     {"INTIMIDATION"}};

                    m["TIEFLING"] = {"TIEFLING", {"INT", "CHA"}, {1, 2}, 'M', 30,
                                     {
                                        {"DARKVISION", "Thanks to your infernal heritage, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray."},
                                        {"HELLISH RESISTANCE", "You have resistance to fire damage."},
                                        {"INFERNAL LEGACY", "You know the thaumaturgy cantrip. When you reach 3rd level, you can cast the hellish rebuke spell as a 2nd-level spell once with this trait and regain the ability to do so when you finish a long rest. When you reach 5th level, you can cast the darkness spell once with this trait and regain the ability to do so when you finish a long rest. Charisma is your spellcasting ability for these spells."}},
                                     {}};

                    return m;
                };
            };
        };

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
            clevel = level;

            abilities = {{"STR", {strength, static_cast<int>((std::floor(strength/2) - 5))}},
                         {"DEX", {dexterity, static_cast<int>((std::floor(dexterity/2) - 5))}},
                         {"CON", {constitution, static_cast<int>((std::floor(constitution/2) - 5))}},
                         {"INT", {intelligence, static_cast<int>((std::floor(intelligence/2) - 5))}},
                         {"WIS", {wisdom, static_cast<int>((std::floor(wisdom/2) - 5))}},
                         {"CHA", {charisma, static_cast<int>(std::floor(charisma/2) - 5)}}};

            weapon = "FISTS";

            setRace(crace);
        }

        ~character() = default;

        character& operator= (const character &a) {
            /**
             * Overriding the assignment operator to copy characters completely
             *
             * @param a The input character
             *
             * @return The copied character
             */

            npc = a.npc;

            weapon = a.weapon;
            cname = a.cname; crace = a.crace; cclass = a.cclass; cbg = a.cbg; clevel = a.clevel;

            abilities = a.abilities;

            hp = a.hp; maxHP = a.maxHP; ac = a.ac; gp = a.gp; speed = a.speed;

            equipment = a.equipment; misc = a.misc; proBonus = a.proBonus; proficiencies = a.proficiencies;
            traits = a.traits; saves = a.saves;

            size = a.size;

            vulnerabilities = a.vulnerabilities; resistances = a.resistances; immunities = a.immunities;
            effects = a.effects;

            return *this;
        }

        character& operator>> (const character &a) {
            /**
             * Overriding the right shift operator to soft copy characters
             *
             * Essentially copies equipment; That's all
             *
             * @param a The input character
             *
             * @return The soft copy of the character
             */

            gp = a.gp;

            equipment = a.equipment; misc = a.misc;

            return *this;
        }

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

        void refreshMods() {
            /**
             * Refresh the ability modifiers
             */

            for (std::pair<std::string, std::array<int, 2> > element : abilities) {
                abilities[element.first][1] = static_cast<int>((std::floor(element.second[0]/2) - 5));
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

        int attack(bool mod = true) {
            /**
             * Used to get the damage from a weapon attack
             *
             * @param mod Whether to add the ability modifier or not; default true
             *
             * @return the damage
             */

            weapons::Weapons weap = weapons::getWeapon(equipment[0]);

            int att = weap.ability;
            int abi = (att == 1)?abilities["DEX"][1]:(att == 2)?abilities["STR"][1]:(att == 3)?(abilities["DEX"][1]>=abilities["STR"][1])?abilities["DEX"][1]:abilities["STR"][1]:0;

            int dmg;

            mod ? dmg = abi : dmg = 0;

            for (int i = 0; i < weap.numberDice; ++i) {
                dmg += weap.die.roll();
            }

            return dmg;
        }

        void damage(int dmg) {
            /**
             * Alters character hp negatively
             */

            hp -= dmg;
        }

        void heal(int heal) {
            /**
             * Alters character hp positively
             */

            hp += heal;

            if (hp > maxHP) {
                hp = maxHP;
            }
        }

    private:
        bool npc;

        std::string weapon;
        std::string cname, cclass, crace, cbg;
        int clevel;
        std::map<std::string, std::array<int, 2> > abilities;

        int hp = 0;
        int maxHP = 0;
        int ac = abilities["DEX"][1] + 10;
        int gp;
        unsigned int speed;

        std::vector<std::string> equipment = {"FISTS", "UNARMORED"}; ///Equipped items
        std::vector<std::string> misc = {}; ///Other items
        unsigned short proBonus = 2;
        std::map<std::string, std::string> traits;
        std::vector<std::string> proficiencies {"COMMON"};
        std::vector<std::string> saves;

        char size = 'M'; ///Sets the size

        ///Mapping the skills to an ability
        std::map<std::string, std::string> skills = {
                {"ATHLETICS", "STR"},
                {"ACROBATICS", "DEX"},
                {"SLEIGHT OF HAND", "DEX"},
                {"STEALTH", "DEX"},
                {"ARCANA", "INT"},
                {"HISTORY", "INT"},
                {"INVESTIGATION", "INT"},
                {"NATURE", "INT"},
                {"RELIGION", "INT"},
                {"ANIMAL HANDLING", "WIS"},
                {"INSIGHT", "WIS"},
                {"MEDICINE", "WIS"},
                {"PERCEPTION", "WIS"},
                {"SURVIVAL", "WIS"},
                {"DECEPTION", "CHA"},
                {"INTIMIDATION", "CHA"},
                {"PERFORMANCE", "CHA"},
                {"PERSUASION", "CHA"}
        };

        ///0 = None, 1 = Acid, 2 = Bludgeoning, 3 = Cold, 4 = Fire, 5 = Force, 6 = Lightning, 7 = Necrotic, 8 = Piercing, 9 = Poison, 10 = Psychic, 11 = Radiant, 12 = Slashing, 13 = Thunder
        std::vector<int> vulnerabilities = {0};
        std::vector<int> immunities = {0};
        std::vector<int> resistances = {0};
        std::vector<std::string> effects;


        void setRace(std::string name) {
            /**
             * Sets the race and abilities and stuff
             *
             * DO NOT RUN AFTER CONSTRUCTION
             */

            race::Race x = race::getRace(name);

            for (int i = 0; i < x.abis.size(); ++i){
                if (x.abis[i] == "HP") {
                    hp += x.boosts[i];
                } else {
                    abilities[x.abis[i]][0] += x.boosts[i];
                }
            }

            refreshMods();

            size = x.size; speed = x.speed;

            traits.insert(x.traits.begin(), x.traits.end());
            proficiencies.insert(proficiencies.end(), x.prof.begin(), x.prof.end());
        }
    };
}

#endif /* CHARACTER_HPP */