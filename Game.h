#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "Player.h"
#include "Map.h"
#include "Container.h"
#include "LocalizationManager.h"


class Command;

class Game {
public:

    enum class GameState { MainMenu, Playing, Paused, GameOver };


    Game(sf::RenderWindow& win);
    ~Game();

    void runGameLoop();


    Player& getPlayer() { return player; }
    Map& getMap() { return map; }
    Container<Entity>& getEnemies() { return enemies; }


    void handlePlayerAttack();


    void setGameOver() { currentState = GameState::GameOver; }

private:
    // Поля класу
    sf::RenderWindow& window;
    GameState currentState;

    Player player;
    Container<Entity> enemies;
    Map map;

    // Графічні ресурси
    sf::Font font;
    sf::Texture floorTexture, wallTexture, playerTexture, zombieTexture, bossTexture;

    // Елементи UI
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

    // Приватні методи
    void loadAssets();
    void setupUI();
    void resetGame();
    void addLogMessage(const std::string& message);
    void centerTextOrigin(sf::Text& text);

    void processEvents();
    void update();
    void render();


    void processMainMenuEvents(sf::Event& event);
    void processPlayingEvents(sf::Event& event);
    void processPausedEvents(sf::Event& event);
    void processGameOverEvents(sf::Event& event);


    void updatePlaying();


    void renderMainMenu();
    void renderPlaying();
    void renderPaused();
    void renderGameOver();
};