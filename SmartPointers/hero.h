//
#ifndef DND_HERO_H
#define DND_HERO_H

#include "hero_info.h"
#include "monster.h"
#include<string>
#include <stdexcept>
#include<iostream>
#include<map>
using namespace std;

class Hero{
private:
    unsigned id;
    string name;
    Hero_Class hero_class;
    Hero_Species hero_species;
    unsigned level;
    unsigned max_hp;
    unsigned current_hp;
    map<string, unsigned > abilities;
    static unsigned next_id;
public:
    Hero(string name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const map<string, unsigned>& abilities);
    unsigned level_up();
    bool fight(Monster& m);
    friend ostream& operator<<(ostream& o, const Hero& obj);

    //GETTER METHODS
    string get_name();
    unsigned get_level();
    unsigned get_id();
    unsigned get_current_hp();
    unsigned get_max_hp();
    map <string, unsigned> get_abilities();
    unsigned get_max_ability();
    Hero_Class get_hero_class();
    Hero_Species get_hero_species();
};

#endif //DND_HERO_H
