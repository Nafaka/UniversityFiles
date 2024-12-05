#include<iostream>
#include<string>
#include<memory>
#include<map>
#include"hero.h"
#include"campaign.h"
#include <stdexcept>
using namespace std;

Campaign::Campaign(std::string name, unsigned int min_level) : name(name), min_level(min_level){
    if(name.empty() || min_level <=0) {throw runtime_error("Not allowed");}
}

void Campaign::add_hero(shared_ptr<Hero> h) {
    if(heroes.find(h->get_id()) != heroes.end() || h->get_level() < min_level ) { throw runtime_error("No go");}
    heroes[h->get_id()] = h;
}

void Campaign::encounter_monster(unsigned id, Monster& m) {
    auto it = heroes.find(id);
    if(it != heroes.end()) {
        shared_ptr<Hero> hero = it->second.lock();
        if(hero && hero->fight(m) > 0) { hero->level_up();}
    }
}

unsigned Campaign::remove_dead_and_expired() {
    unsigned counter = 0;
    for(auto it = heroes.begin(); it !=  heroes.end();){
        shared_ptr<Hero> hero = it->second.lock();
        if(!hero || hero->get_current_hp() == 0){
            it =  heroes.erase(it);
            ++counter;
        } else { ++it;}
    }
    return counter;
}

ostream& operator<<(ostream& o, const Campaign& p){
    o << "[" << p.name << " Campaign, Min_Level " << p.min_level << ", {";
    for (auto it = p.heroes.begin(); it != p.heroes.end(); ++it) {
        shared_ptr<Hero> hero = it->second.lock();
        if (hero) {
            o << "[" << hero->get_id() << ", " << hero->get_name() << ", (" << hero_class_names[hero->get_hero_class()] << ", " << hero_species_names[hero->get_hero_species()]  << ", " << hero->get_level() << "), {";
            const auto& abilities = hero->get_abilities();
            for (auto itt = abilities.begin(); itt != abilities.end(); ++itt) {
                o << itt->second;
                if (next(itt) != abilities.end()) {
                    o << ", ";
                }
            }
            o << "}, (" << hero->get_current_hp() << "/" << hero->get_max_hp() << ") HP]";
            if (next(it) != p.heroes.end()) {
                o << ", ";
            }
        }
    }
    o << "}]";

    return o;
}