#pragma once

#ifndef EZDND_ARMOR_HPP
#define EZDND_ARMOR_HPP

#include <string>
#include <map>

namespace dnd {
    class armor {
    public:
        struct Armor {
            std::string name;
            unsigned short baseAC; ///The base amount the armour protects with 0 dex
            unsigned short dexMax; ///The amount of allowed dex (0 = no dex, 10 = no limit)
            char armType; ///'N' = None, L' = Light, 'M' = Medium, 'H' = Heavy
            bool disadvantage; ///Whether there is disadvantage on stealth or not
            unsigned short don; ///The time -- in minutes -- it takes to don the armor
            unsigned short doff; ///The time -- in minutes -- it takes to doff the armor
            unsigned short strength; ///The minimum required strength
        };

        armor() = default;
        ~armor() = default;


        static Armor getArmor(const std::string& name){
            /**
             * Easy access to the armor map
             *
             * @return The armor requested
             */

            return A::createMap().at(name);
        }


    private:
        struct A {
            static std::map<std::string, Armor> createMap(){
                /**
                 * Returns the armor map
                 *
                 * Map parameters are the armor struct
                 *
                 * @return The armor map
                 */

                std::map<std::string, Armor> m;

                m["UNARMORED"] = {"UNARMORED", 10, 10, 'N', false, 0, 0, 0};
                m["PADDED"] = {"PADDED", 11, 10, 'L', true, 1, 1, 0};
                m["LEATHER"] = {"LEATHER", 11, 10, 'L', false, 1, 1, 0};
                m["STUDDED LEATHER"] = {"STUDDED LEATHER", 12, 10, 'L', false, 1, 1, 0};
                m["HIDE"] = {"HIDE", 12, 2, 'M', false, 5, 1, 0};
                m["CHAIN SHIRT"] = {"CHAIN SHIRT", 13, 2, 'M', false, 5, 1, 0};
                m["SCALE MAIL"] = {"SCALE MAIL", 14, 2, 'M', true, 5, 1, 0};
                m["BREASTPLATE"] = {"BREASTPLATE", 14, 2, 'M', false, 5, 1, 0};
                m["HALF PLATE"] = {"HALF PLATE", 15, 2, 'M', true, 5, 1, 0};
                m["RING MAIL"] = {"RING MAIL", 14, 0, 'H', true, 10, 5, 0};
                m["CHAIN MAIL"] = {"CHAIN MAIL", 16, 0, 'H', true, 10, 1, 13};
                m["SPLINT"] = {"SPLINT", 17, 0, 'H', true, 10, 5, 15};
                m["PLATE"] = {"PLATE", 18, 0, 'H', true, 10, 5, 15};

                return m;
            };
        };
    };
}

#endif /* EZDND_ARMOR_HPP */