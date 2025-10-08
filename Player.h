#pragma once
#include<iostream>
#include<vector>
#include"Entity.h"
#include "Weapon.h"
#include "Sword.h"
#include "Gun.h"

using namespace std;

#ifndef UNTITLED23_PLAYER_H
#define UNTITLED23_PLAYER_H

#endif //UNTITLED23_PLAYER_H



class Player : public Entity {
    int score;
    int x, y;
    Weapon* weapon;
    bool weaponChosen;
public:
    Player(const string& n, int h, int d, int sx, int sy)
            : Entity(n, h, d), weapon(nullptr), score(0), x(sx), y(sy) {}

    void chooseWeapon(int choice) {
        if (weaponChosen) {
            cout << "Weapon already chosen: " << weapon->getName() << endl;
            return;
        }

        if (choice == 1) weapon = new Sword();
        else if (choice == 2) weapon = new Gun();
        else {
            cout << "Invalid choice! Defaulting to Sword." << endl;
            weapon = new Sword();
        }

        weaponChosen = true;
        cout << name << " equipped " << weapon->getName() << endl;
    }

    void openInventory() {
        cout << "Inventory: " << (weapon ? weapon->getName() : "empty") << endl;
    }

    void attack(Entity& target) override {
        cout << "\n[PLAYER ATTACK]" << endl;
        cout << name << " (" << health << " HP) attacks " << target.getName()
             << " (" << target.getHealth() << " HP)" << endl;

        if (!weapon) {
            cout << name << " has no weapon equipped!" << endl;
            return;
        }

        int totalDamage = damage + weapon->getDamage();
        cout << ">>> Deals " << totalDamage << " damage with " << weapon->getName() << endl;
        target.takeDamage(totalDamage);
        cout << target.getName() << " now has " << target.getHealth() << " HP\n";
    }

    void addScore(int points) { score += points; }
    int getScore() const { return score; }
    int getX() const { return x; }
    int getY() const { return y; }

    void move(int dx, int dy, const vector<vector<int>>& map) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx >= 0 && nx < (int)map[0].size() && ny >= 0 && ny < (int)map.size()) {
            if (map[ny][nx] == 0) {
                x = nx;
                y = ny;
            } else {
                cout << "Can't move there (wall)." << endl;
            }
        }
    }

    ~Player() {
        delete weapon;
    }
};