#include <iostream>
#include "Character/character.hpp"
#include "Core/dice.hpp"

using std::cout;
using std::cin;
using std::endl;

int main(){
    dnd::character fred = dnd::character("Fred", "Rogue", "Human", "Acolyte", 1, 10, 10, 10, 10, 10, 10, false);

    cout << fred.getAbilities()["STR"] << endl;
    cout << fred.getName() << endl;
    cout << fred.getClass() << endl;
    cout << fred.getRace() << endl;
    cout << fred.getBg() << endl;

    cout << dnd::d4.roll() << endl;
    cout << dnd::d6.roll() << endl;
    cout << dnd::d8.roll() << endl;
    cout << dnd::d10.roll() << endl;
    cout << dnd::d12.roll() << endl;
    cout << dnd::d20.roll() << endl;
    cout << dnd::d100.roll() << endl;

    return 0;
}