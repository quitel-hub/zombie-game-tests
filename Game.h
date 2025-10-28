// #include<iostream>
// #include<vector>
// #include"Entity.h"
// #include "Zombie.h"
// #include "Player.h"
// #include "Boss.h"
// #include "Sword.h"
// #include "Gun.h"
// #include "Inventory.h"
// #include "Map.h"
// #include "Container.h"
// #include "LocalizationManager.h"
//
//
// #pragma once
//
// using namespace std;
//
// #ifndef UNTITLED23_GAME_H
// #define UNTITLED23_GAME_H
//
// #endif //UNTITLED23_GAME_H
//
// class Game {
//     Player player;
//     Container<Entity> enemies;
//     Map map;
//
// public:
//     Game() : player("Player", 100, 20, 1, 1), map(15, 15, 20) {
//         enemies.add(make_unique<Zombie>("Zombie 1", 50, 10, 5, 5));
//         enemies.add(make_unique<Zombie>("Zombie 2", 60, 15, 10, 3));
//         enemies.add(make_unique<Boss>("BOSS", 120, 20, 10, 7, 7));
//     }
//
//     void run() {
//         cout << L10N.getString("game_start") << endl;
//         cout << L10N.getString("choose_weapon");
//         int choice; cin >> choice;
//         player.chooseWeapon(choice);
//
//         while (player.isAlive() && enemies.size() > 0) {
//             cout << L10N.getFormattedString("health_score_hud", player.getHealth(), player.getScore()) << endl;
//             map.render(player, enemies.getAllRaw());
//
//             cout << L10N.getString("player_turn_header") << endl;
//             cout << L10N.getString("player_turn_prompt");
//             char c; cin >> c; c = tolower(c);
//
//             if (c == 'q') break;
//             if (c == 'w') player.move(0, -1, map.getGrid());
//             if (c == 's') player.move(0, 1, map.getGrid());
//             if (c == 'a') player.move(-1, 0, map.getGrid());
//             if (c == 'd') player.move(1, 0, map.getGrid());
//
//             if (c == 'f') {
//                 bool attacked = false;
//                 for (size_t i = 0; i < enemies.size(); ++i) {
//                     Entity* enemy_ptr = enemies.get(i);
//                     Zombie* z = dynamic_cast<Zombie*>(enemy_ptr);
//                     if (z) {
//                         int dx = abs(z->getX() - player.getX());
//                         int dy = abs(z->getY() - player.getY());
//                         if (dx + dy == 1) {
//                             player.attack(*z);
//                             attacked = true;
//                             if (!z->isAlive()) {
//                                 cout << L10N.getFormattedString("enemy_defeated", z->getName()) << endl;
//                                 player.addScore(50);
//                                 enemies.remove(i);
//                                 i--;
//                             }
//                             break;
//                         }
//                     }
//                 }
//                 if (!attacked) {
//                     cout << L10N.getString("no_enemy_in_range") << endl;
//                 } else {
//                     continue;
//                 }
//             }
//
//             if (player.isAlive()) {
//                 cout << L10N.getString("enemy_turn_header") << endl;
//                 for (auto* e : enemies.getAllRaw()) {
//                     Zombie* z = dynamic_cast<Zombie*>(e);
//                     if (z) {
//                         int dx = abs(z->getX() - player.getX());
//                         int dy = abs(z->getY() - player.getY());
//                         if (dx + dy == 1) {
//                             z->attack(player);
//                             if (!player.isAlive()) {
//                                 cout << L10N.getString("player_fallen") << endl;
//                                 break;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//
//         if (player.isAlive()) cout << L10N.getString("victory") << endl;
//         else cout << L10N.getString("defeat") << endl;
//         cout << L10N.getFormattedString("final_score", player.getScore()) << endl;
//     }
// };
#pragma once
#include <SFML/Graphics.hpp> // <-- Переконайтесь, що SFML включено
#include <map>
#include <memory>
#include <vector>
#include <deque>
#include "Player.h"
#include "Map.h"
#include "Container.h"
#include "LocalizationManager.h"

// Випереджаюче оголошення
class Command;

class Game {
public:
    // Стани гри
    enum class GameState { MainMenu, Playing, Paused, GameOver };

    // --- Публічні методи ---
    Game(sf::RenderWindow& win); // Конструктор
    ~Game();                    // Деструктор

    void runGameLoop();         // Головний ігровий цикл

    // Методи доступу (залишаємо)
    Player& getPlayer() { return player; }
    Map& getMap() { return map; }
    Container<Entity>& getEnemies() { return enemies; }

    // Метод для обробки атаки гравця (зроблено публічним)
    void handlePlayerAttack();

    // Метод для завершення гри
    void setGameOver() { currentState = GameState::GameOver; }

private:
    // --- Поля класу ---
    sf::RenderWindow& window;
    GameState currentState;

    Player player;
    Container<Entity> enemies;
    Map map;

    // Графічні ресурси
    sf::Font font;
    sf::Texture floorTexture, wallTexture, playerTexture, zombieTexture, bossTexture;

    // Елементи UI (як були)
    sf::Text menuTitleText, playButtonText, exitButtonText;
    sf::RectangleShape playButton, exitButton;
    sf::Text pauseTitleText, resumeButtonText, pauseExitButtonText;
    sf::RectangleShape resumeButton, pauseExitButton;
    sf::Text gameOverTitleText, finalScoreText, restartButtonText, gameOverExitButtonText;
    sf::RectangleShape restartButton, gameOverExitButton;
    sf::Text healthText, scoreText;
    std::deque<sf::Text> logMessages;
    const size_t MAX_LOG_MESSAGES = 4;

    bool isPlayerTurn = true;

    // --- Приватні методи ---
    void loadAssets();
    void setupUI();
    void resetGame();
    void addLogMessage(const std::string& message);
    void centerTextOrigin(sf::Text& text); // Допоміжний метод

    // Методи головного циклу
    void processEvents();
    void update();
    void render();

    // Обробники подій для станів
    void processMainMenuEvents(sf::Event& event);
    void processPlayingEvents(sf::Event& event);
    void processPausedEvents(sf::Event& event);
    void processGameOverEvents(sf::Event& event);

    // Оновлення логіки для стану гри
    void updatePlaying();

    // Методи рендерингу для станів
    void renderMainMenu();
    void renderPlaying();
    void renderPaused();
    void renderGameOver();
};