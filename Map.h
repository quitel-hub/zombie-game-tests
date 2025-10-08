#include<iostream>
#include<vector>
#include<cstdlib>
#include"Entity.h"
#include "Zombie.h"
#include "Player.h"
#include "Boss.h"
#pragma once


using namespace std;
#ifndef UNTITLED23_MAP_H
#define UNTITLED23_MAP_H

#endif //UNTITLED23_MAP_H


class Map {
    int width, height;
    vector<vector<int>> grid;
public:
    Map(int w, int h, int wallPercent) : width(w), height(h) {
        grid = vector<vector<int>>(h, vector<int>(w, 0));
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (y == 0 || y == h - 1 || x == 0 || x == w - 1)
                    grid[y][x] = 1;
                else
                    grid[y][x] = (rand() % 100 < wallPercent) ? 1 : 0;
            }
        }
    }

    const vector<vector<int>>& getGrid() const { return grid; }

    void render(const Player& p, const vector<Entity*>& enemies) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (x == p.getX() && y == p.getY()) cout << 'P';
                else {
                    bool enemyHere = false;
                    for (auto e : enemies) {
                        Zombie* z = dynamic_cast<Zombie*>(e);
                        if (z && z->getX() == x && z->getY() == y) {
                            if (dynamic_cast<Boss*>(e)) cout << 'B';
                            else cout << 'Z';
                            enemyHere = true;
                            break;
                        }
                    }
                    if (!enemyHere) cout << (grid[y][x] == 1 ? '#' : '.');
                }
            }
            cout << endl;
        }
    }
};