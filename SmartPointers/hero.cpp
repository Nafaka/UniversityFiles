#include "hero.h"
#include "hero_info.h"
#include "monster.h"
#include <string>
#include <cstdlib>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <stdexcept>

unsigned Hero::next_id = 0;

Hero::Hero(string name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const std::map<std::string,unsigned>& abilities)
        : name(name), hero_class(hero_class), hero_species(hero_species), max_hp(max_hp), abilities(abilities) {
    this->level = 1;
    this->current_hp = max_hp;
    if(name.empty() || level <= 0 || level>=21 || max_hp <= 0 || current_hp > max_hp){throw std::runtime_error("OUT OF REACH");}
    if(abilities.size() != 6)
        throw std::runtime_error("Abilities must be 6 types");
    for (const auto& [key, value] : abilities) {
        if (value <= 0 || value >= 21)
            throw std::runtime_error("Abilities must be between 1 and 20");
        if (key != "Strength" && key != "Dexterity" && key != "Constitution" && key != "Intelligence" && key != "Wisdom" && key != "Charisma")
            throw std::runtime_error("Invalid ability");
    }
    this->id = next_id++;
}

unsigned Hero::level_up() {
    if(level < 20) ++level;
    return level;
}

bool Hero::fight(Monster& m) {
    while(current_hp > 0 && m.get_health() > 0){
        if(current_hp > 0) { m.take_damage(level * get_max_ability());
            if(m.get_health() > 0) {
                if(current_hp > m.get_attack()) { current_hp -= m.get_attack(); }
                else { current_hp = 0; }
            }
        }
    }
    if(current_hp > 0) { return true;}
    return false;
}

ostream& operator<<(ostream& o, const Hero& obj){
    o << "[" << obj.id << ", " << obj.name << ", (" << hero_class_names[obj.hero_class] << ", " << hero_species_names[obj.hero_species] << ", " << obj.level << "), {";
    for(auto it = obj.abilities.begin(); it != obj.abilities.end(); ++it){
        o << it -> second;
        if(next(it) != obj.abilities.end()){ o << ", ";}
    }
    o << "}, (" << obj.current_hp << "/" << obj.max_hp<< ") HP]";
    return o;
}

//GETTER METHODS
string Hero::get_name(){ return name; }
unsigned Hero::get_level(){ return level; }
unsigned Hero::get_id(){ return id; }
unsigned Hero::get_current_hp(){ return current_hp; }
unsigned Hero::get_max_hp(){ return max_hp; }
map <string, unsigned> Hero::get_abilities(){ return abilities; }
Hero_Class Hero::get_hero_class(){ return hero_class; }
Hero_Species Hero::get_hero_species(){ return hero_species; }
unsigned Hero::get_max_ability(){
    unsigned max = 0;
    for(const auto& ab : abilities){
        if(ab.second > max ) { max = ab.second;}
    }
    return max;
}
