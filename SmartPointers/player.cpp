#include "player.h"
#include "hero_info.h"
#include "hero.h"
#include "campaign.h"
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <stdexcept>

Player::Player(string first_name, string last_name): first_name(first_name), last_name(last_name){
    if (first_name.empty() || last_name.empty()){ throw runtime_error("No go");}
}

unsigned Player::create_hero(const string& name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const map<string, unsigned> abilities){
    auto hero = make_shared<Hero>(name, hero_class, hero_species, max_hp, abilities);
    heroes[hero->get_id()] = hero;
    return hero->get_id();
}

void Player::create_campaign(string name, unsigned min_level, unsigned id){
    auto it = heroes.find(id);
    if(it ==  heroes.end()){ throw runtime_error("No go");}
    campaign = make_unique<Campaign>(name, min_level);
    campaign->add_hero(heroes[id]);
}

void Player::join_friends_campaign(Player& pfriend, unsigned id){
    if(!pfriend.campaign) { throw runtime_error("No go");}
    auto it = heroes.find(id);
    if (it == heroes.end()) { throw runtime_error("No go"); }
    pfriend.campaign->add_hero(heroes[id]);
}

void Player::transfer_campaign(Player& pfriend){
    if(!campaign) {throw runtime_error("No go");}
    if(pfriend.campaign){ pfriend.campaign.reset();}
    pfriend.campaign = move(campaign);
}

unsigned Player::remove_dead(){
    unsigned counter = 0;
    for (auto it = heroes.begin(); it != heroes.end();){
        if(it->second->get_current_hp() == 0) {
            it = heroes.erase(it);
            ++counter;
        }else { ++it;}
    }
    return counter;
}

ostream& Player::print_campaign(ostream& o)const{
    if(!campaign) {o << "[]";}
    else {o << *campaign;}
    return o;
}

ostream& operator<<(ostream& o, const Player& p){
    o << "[" << p.first_name << " " << p.last_name << ", {";
    bool first = true;
    for (const auto& [id, hero] : p.heroes) {
        if (!first) {
            o << ", ";
        }
        first = false;
        o << *hero;
    }
    o << "}, ";
    p.print_campaign(o);
    o << "]";
    return o;
}