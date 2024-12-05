#include "monster.h"
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <stdexcept>

Monster::Monster(std::string name, unsigned health, unsigned attack) : name(name), health(health), attack(attack) {
    if(name.empty() || health == 0 || attack == 0) { throw runtime_error("No go");}
}

void Monster::take_damage(unsigned dmg) {
    unsigned damage = calculate_damage(dmg);
    health = (health > damage) ? (health - damage) : 0;
}

bool Monster::is_dead() const {
    return health <= 0;
}

ostream& operator<<(ostream& o, const Monster& h){
    o << "[" << h.name << ", " << h.health << " HP, " << h.attack << " ATK" << h.additional_information() << "]";
    return o;
}

//ELITE MONSTER
Elite_Monster::Elite_Monster(std::string name, unsigned health, unsigned attack, unsigned defense) : Monster(name, health, attack), defense(defense){
    if(defense == 0) { throw runtime_error("No go");}
}

unsigned Elite_Monster::calculate_damage(unsigned dmg) const {
    dmg = (dmg > defense) ? (dmg - defense) : 0;
    return dmg;
}

string Elite_Monster::additional_information() const {
    return ", " + to_string(defense) + " DEF";
}

//STANDARD MONSTER
Standard_Monster::Standard_Monster(string name, unsigned health, unsigned attack) : Monster(name, health, attack){}

unsigned Standard_Monster::calculate_damage(unsigned dmg) const {
    return dmg;
}

string Standard_Monster::additional_information() const {
    return "";
}

//GETTER METHODS
string Monster::get_name() {return name;}
unsigned Monster::get_health(){ return health;}
unsigned Monster::get_attack(){ return attack; }
