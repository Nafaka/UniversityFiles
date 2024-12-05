#ifndef DND_PLAYER_H
#define DND_PLAYER_H
#include"campaign.h"
#include "hero_info.h"
#include "hero.h"
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <cstdlib>
#include <stdexcept>
using namespace std;

class Player{
private:
    string first_name;
    string last_name;
    map< unsigned, shared_ptr<Hero>> heroes;
    unique_ptr< Campaign> campaign;
public:
    Player(string first_name, string last_name);
    unsigned create_hero(const string& name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const map<string, unsigned> abilities);
    void create_campaign(string name, unsigned min_level, unsigned id);
    void join_friends_campaign(Player& pfriend, unsigned id);
    void transfer_campaign(Player& pfriend);
    unsigned remove_dead();
    ostream& print_campaign(ostream& o)const;
    friend ostream& operator<<(ostream& o, const Player& p);
};

#endif //DND_PLAYER_H
