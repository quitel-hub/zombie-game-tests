#include<iostream>
#include<vector>
#include <map>
#include <memory>
#include"Entity.h"
#include "Zombie.h"
#include "Player.h"
#include "Boss.h"
#include "Sword.h"
#include "Gun.h"
#include "Inventory.h"
#include "Map.h"
#include "Container.h"
#include "LocalizationManager.h"


#pragma once

using namespace std;

#ifndef UNTITLED23_GAME_H
#define UNTITLED23_GAME_H

#endif //UNTITLED23_GAME_H

class Command;


class Game {
private:
    Player player;
    Container<Entity> enemies;
    Map map;
    bool isGameOver = false;
    std::map<char, unique_ptr<Command>> commands;

public:
    Game();
    ~Game();

    void run();


    Player& getPlayer() { return player; }
    Map& getMap() { return map; }
    Container<Entity>& getEnemies() { return enemies; }
    void handlePlayerAttack();
    void setGameOver() { isGameOver = true; }
};