#ifndef SMARTPONTER_HERO_H
#define SMARTPONTER_HERO_H

#include <iostream>
#include <map>
#include "hero_info.h"
#include "monster.h"
using namespace std;

class Hero{
private:
    string name;
    Hero_Class hero_class;
    Hero_Species hero_species;
    unsigned level;
    unsigned max_hp;
    unsigned current_hp;
    map<string, unsigned > abilities;
    static unsigned next_id;
public:
    Hero(string name, Hero_Class hero_class, Hero_Species hero_speccies, unsigned max_hp, const map<string, unsigned >&);
    unsigned level_up();
    bool fight(Monster& m);
    friend ostream& operator<<(ostream& o, const Hero& obj);
};

#endif //SMARTPONTER_HERO_H
