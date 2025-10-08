#pragma once
#include<iostream>
using namespace std;

#ifndef UNTITLED23_ENTITY_H
#define UNTITLED23_ENTITY_H

#endif //UNTITLED23_ENTITY_H


class Entity {
protected:
    string name;
    int health;
    int damage;
public:
    Entity(const string& n, int h, int d) : name(n), health(h), damage(d) {}
    virtual void attack(Entity& target) = 0;
    virtual void takeDamage(int dmg) {
        cout << name << " takes " << dmg << " damage!" << endl;
        health -= dmg;
        if (health < 0) health = 0;
    }
    bool isAlive() const { return health > 0; }
    string getName() const { return name; }
    int getHealth() const { return health; }
    int getDamage() const { return damage; }
    virtual ~Entity() {}
};