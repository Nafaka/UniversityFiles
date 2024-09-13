#ifndef SMARTPONTER_MONSTER_H
#define SMARTPONTER_MONSTER_H

#include <iostream>
#include <map>
#include "hero_info.h"
#include "hero.h"
#include "campaign.h"
using namespace std;

class Monster{
private:
    string name;
    unsigned health;
    unsigned attack;
public:
    Monster(string name, unsigned health, unsigned attack);
    virtual ~Monster();
    virtual unsigned calculate_damage(unsigned dmg) const;
    void take_damage(unsigned dmg);
    bool is_dead() const;
    virtual string additional_information() const;
    friend ostream& operator<<(ostream& o, const Monster& h);
};

class Elite_Monster : public Monster{
private:
    unsigned defense;
public:
    Elite_Monster(string name, unsigned health, unsigned attack, unsigned defense);
    unsigned calculate_damage(unsigned dmg);
    string additional_information() const;
};

class Standard_Monster : public Monster{
public:
    Standard_Monster(string name, unsigned health, unsigned attack);
    unsigned calculate_damage(unsigned dmg);
    string additional_information() const;
};

#endif //SMARTPONTER_MONSTER_H
