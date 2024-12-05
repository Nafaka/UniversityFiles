#ifndef DND_CAMPAIGN_H
#define DND_CAMPAIGN_H
#include<iostream>
#include <stdexcept>
#include<string>
#include<memory>
#include<map>
#include"hero.h"
using namespace std;

class Campaign{
private:
    string name;
    map< unsigned, weak_ptr<Hero>> heroes;
    unsigned min_level;
public:
    Campaign(string name, unsigned min_level);
    void add_hero(shared_ptr<Hero> h);
    void encounter_monster(unsigned id, Monster& m);
    unsigned remove_dead_and_expired();
    friend ostream& operator<<(ostream& o, const Campaign& p);

};

#endif //DND_CAMPAIGN_H
