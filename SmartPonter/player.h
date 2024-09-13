#ifndef SMARTPONTER_PLAYER_H
#define SMARTPONTER_PLAYER_H

#include <iostream>
#include <map>
#include "hero_info.h"
#include "hero.h"
#include "campaign.h"
#include "monster.h"
using namespace std;

class Player {
private:
    string first_name;
    string last_name;
    map<unsigned, shared_ptr<Hero>> ids;
    unique_ptr<Campaign> campaign;
public:
    Player(string first_name, string last_name);
    unsigned create_hero(const string&, Hero_Class, Hero_Species, unsigned health, const map<string, unsigned>&);
    void create_campaign(string name, unsigned min_level, unsigned id);
    void join_friends_campaign(Player& freund, unsigned id);
    void transfer_campaign(Player& freund);
    unsigned remove_dead();
    ostream& print_campaign(ostream&);
    friend ostream& operator<<(ostream& o, const Player& p);

};

#endif //SMARTPONTER_PLAYER_H
