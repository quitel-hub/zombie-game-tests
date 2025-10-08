#include<iostream>
#include<vector>
#include"Entity.h"
#include "Zombie.h"
#include "Player.h"
#include "Boss.h"
#include "Sword.h"
#include "Gun.h"
#include "Inventory.h"
#include "Map.h"
#include "Container.h"


#pragma once

using namespace std;

#ifndef UNTITLED23_GAME_H
#define UNTITLED23_GAME_H

#endif //UNTITLED23_GAME_H

class Game {
    Player player;
    Container<Entity> enemies;
    Container<Weapon> inventory;
    Map map;

public:
    Game() : player("Player", 100, 20, 1, 1), map(15, 15, 20) {
        enemies.add(new Zombie("Zombie 1", 50, 10, 5, 5));
        enemies.add(new Zombie("Zombie 2", 60, 15, 10, 3));
        enemies.add(new Boss("BOSS", 120, 20, 10, 7, 7));

        inventory.add(new Sword());
        inventory.add(new Gun());
    }

    void run() {
        cout << "=== GAME START ===" << endl;
        cout << "Choose weapon:\n1 - Sword\n2 - Gun\n";
        int choice; cin >> choice;
        player.chooseWeapon(choice);

        while (player.isAlive() && enemies.size() > 0) {
            cout << "\nHealth: " << player.getHealth() << " | Score: " << player.getScore() << endl;
            map.render(player, enemies.getAll());

            cout << "\n--- PLAYER TURN ---" << endl;
            cout << "W/A/S/D to move, F to attack, Q to quit: ";
            char c; cin >> c; c = tolower(c);

            if (c == 'q') break;
            if (c == 'w') player.move(0, -1, map.getGrid());
            if (c == 's') player.move(0, 1, map.getGrid());
            if (c == 'a') player.move(-1, 0, map.getGrid());
            if (c == 'd') player.move(1, 0, map.getGrid());

            if (c == 'f') {
                bool attacked = false;
                for (size_t i = 0; i < enemies.size(); ++i) {
                    Zombie* z = dynamic_cast<Zombie*>(enemies.get(i));
                    if (z) {
                        int dx = abs(z->getX() - player.getX());
                        int dy = abs(z->getY() - player.getY());
                        if (dx <= 1 && dy <= 1) {
                            player.attack(*z);
                            attacked = true;
                            if (!z->isAlive()) {
                                cout << z->getName() << " defeated!" << endl;
                                player.addScore(50);
                                enemies.remove(i);
                            }
                            break;
                        }
                    }
                }
                if (!attacked)
                    cout << "No enemies in range to attack!" << endl;
            }

            if (player.isAlive()) {
                cout << "\n--- ENEMY TURN ---" << endl;
                for (auto* e : enemies.getAll()) {
                    Zombie* z = dynamic_cast<Zombie*>(e);
                    if (z) {
                        int dx = abs(z->getX() - player.getX());
                        int dy = abs(z->getY() - player.getY());
                        if (dx <= 1 && dy <= 1) {
                            z->attack(player);
                            if (!player.isAlive()) {
                                cout << "Player has fallen!" << endl;
                                break;
                            }
                        }
                    }
                }
            }
        }

        if (player.isAlive()) cout << "\n=== Victory! All enemies defeated! ===" << endl;
        else cout << "\n=== Defeat... ===" << endl;
        cout << "Final score: " << player.getScore() << endl;
    }
};
