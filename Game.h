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

private:
    sf::RenderWindow& window;
    GameState currentState;
    void centerTextOrigin(sf::Text& text);

    // Ігрові об'єкти
    Player player;
    Container<Entity> enemies;
    Map map;

    // Графічні ресурси
    sf::Font font;
    sf::Texture floorTexture, wallTexture, playerTexture, zombieTexture, bossTexture;

    // --- Елементи інтерфейсу ---
    // Головне меню
    sf::Text menuTitleText;
    sf::RectangleShape playButton;
    sf::Text playButtonText;
    sf::RectangleShape exitButton;
    sf::Text exitButtonText;

    // Меню паузи
    sf::Text pauseTitleText;
    sf::RectangleShape resumeButton;
    sf::Text resumeButtonText;
    sf::RectangleShape pauseExitButton; // Інша назва, щоб не плутати
    sf::Text pauseExitButtonText;

    // Екран кінця гри
    sf::Text gameOverTitleText;
    sf::Text finalScoreText;
    sf::RectangleShape restartButton;
    sf::Text restartButtonText;
    sf::RectangleShape gameOverExitButton;
    sf::Text gameOverExitButtonText;

    // Ігровий HUD та лог
    sf::Text healthText;
    sf::Text scoreText;
    std::deque<sf::Text> logMessages;
    const size_t MAX_LOG_MESSAGES = 4;

    bool isPlayerTurn = true;


    void loadAssets();
    void setupUI();


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


    void handlePlayerAttack();
    void addLogMessage(const std::string& message);
    void resetGame();

public:
    Game(sf::RenderWindow& win);
    ~Game();

    void runGameLoop();


    Player& getPlayer() { return player; }
    Map& getMap() { return map; }
    Container<Entity>& getEnemies() { return enemies; }
};