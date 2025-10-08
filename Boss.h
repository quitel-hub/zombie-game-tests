#pragma once
#include<iostream>
#include"Zombie.h"

using namespace std;

#ifndef UNTITLED23_BOSS_H
#define UNTITLED23_BOSS_H

#endif //UNTITLED23_BOSS_H




class Boss : public Zombie {
    int rage;
public:
    Boss(const string& n, int h, int d, int r, int sx, int sy)
            : Zombie(n, h, d, sx, sy), rage(r) {}

    void attack(Entity& target) override {
        int totalDamage = getDamage() + rage;
        cout << "\n[BOSS ATTACK]" << endl;
        cout << getName() << " in rage! (" << getHealth() << " HP) attacks "
             << target.getName() << " (" << target.getHealth() << " HP)" << endl;
        target.takeDamage(totalDamage);
        cout << target.getName() << " now has " << target.getHealth() << " HP\n";
    }
};
