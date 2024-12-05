#ifndef DND_HERO_INFO_H
#define DND_HERO_INFO_H

#include <memory>
#include <string>
#include <iostream>
#include <map>
#include<vector>
using namespace std;


enum Hero_Class { BARBARIAN, BARD, CLERIC, DRUID, FIGHTER, MONK, PALADIN, RANGER, ROGUE, SORCERER, WARLOCK, WIZARD };
enum Hero_Species { DRAGONBORN, DWARF, ELF, GNOME, HALF_ELF, HALFLING, HALF_ORC, HUMAN, TIEFLING };
const std::vector<std::string> hero_class_names{"Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue", "Sorcerer", "Warlock", "Wizard"};
const std::vector<std::string> hero_species_names{"Dragonborn", "Dwarf", "Elf", "Gnome", "Half-Elf", "Halfling", "Half-Orc", "Human", "Tiefling"};

inline ostream& operator<<(ostream& o, Hero_Class m) {
    o << hero_class_names[m];
    return o;
}

inline ostream& operator<<(ostream& o, Hero_Species m){
    o << hero_species_names[m];
    return o;
}

#endif //DND_HERO_INFO_H
