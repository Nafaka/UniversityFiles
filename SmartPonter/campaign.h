#ifndef SMARTPONTER_CAMPAIGN_H
#define SMARTPONTER_CAMPAIGN_H

#include <iostream>
#include <map>
#include "hero.h"
#include "monster.h"
using namespace std;


class Campaign{
private:
    string name;
    map<unsigned, weak_ptr<Hero>> ids;
    unsigned min_level;
public:
    Campaign(string, unsigned min_level);
    void add_hero(shared_ptr<Hero> h);
    void encounter_monster(unsigned id, Monster& m);
    unsigned remove_dead_and_expired();
    friend ostream& operator<<(ostream& o, const Campaign& p);
};

#endif //SMARTPONTER_CAMPAIGN_H
