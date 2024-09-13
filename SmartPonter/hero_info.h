#ifndef SMARTPONTER_HERO_INFO_H
#define SMARTPONTER_HERO_INFO_H

#include <iostream>
#include <map>
using namespace std;


enum class Hero_Class{ BARBARIAN, BARD, CLERIC, DRUID, FIGHTER, MONK, PALADIN, RANGER, ROGUE, SORCERER, WARLOCK, WIZARD};
enum class Hero_Species{ DRAGONBORN, DWARF, ELF, GNOME, HALF_ELF, HALFLING, HALF_ORC, HUMAN, TIEFLING};

class Hero_Enums{
public:
    friend ostream& operator<<(ostream& o, Hero_Class m);
    friend ostream& operator<<(ostream& o, Hero_Species m);
};

#endif //SMARTPONTER_HERO_INFO_H
