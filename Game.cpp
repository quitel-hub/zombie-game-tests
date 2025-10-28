//#include "Game.h"
//#include "Zombie.h"
//#include "Boss.h"
//#include <iostream>
//#include <string> // Для std::to_string
//
////Конструктор та налаштування
//
//Game::Game(sf::RenderWindow& win)
//    : window(win),
//      currentState(GameState::MainMenu),
//      player("Player", 100, 20, 1, 1),
//      map(15, 15, 20)
//{
//    loadAssets();
//    setupUI();
//    resetGame();
//}
//
//Game::~Game() = default;
//
//void Game::loadAssets() {
//    if (!font.loadFromFile("3Dumb.ttf")) { std::cout << "Error: Could not load font 'arial.ttf'" << std::endl; }
//    if (!playerTexture.loadFromFile("player.png")) { std::cout << "Error loading player.png" << std::endl; }
//    if (!zombieTexture.loadFromFile("zombie.png")) { std::cout << "Error loading zombie.png" << std::endl; }
//    if (!bossTexture.loadFromFile("boss.png"))   { std::cout << "Error loading boss.png" << std::endl; }
//    if (!wallTexture.loadFromFile("wall.png"))     { std::cout << "Error loading wall.png" << std::endl; }
//    if (!floorTexture.loadFromFile("floor.png"))   { std::cout << "Error loading floor.png" << std::endl; }
//}
//
//void Game::setupUI() {
//    float centerX = window.getSize().x / 2.0f;
//    float buttonWidth = 200.f;
//    float buttonHeight = 50.f;
//    sf::Color buttonColor(100, 100, 100);
//    sf::Color textColor = sf::Color::White;
//    unsigned int charSize = 24;
//    unsigned int titleCharSize = 50;
//
//
//
//    //Головне меню
//    menuTitleText.setFont(font);
//    menuTitleText.setString("Zombie Survival");
//    menuTitleText.setCharacterSize(titleCharSize);
//    menuTitleText.setFillColor(textColor);
//    centerTextOrigin(menuTitleText);
//    menuTitleText.setPosition(centerX, window.getSize().y / 4.0f);
//
//    playButton.setSize({buttonWidth, buttonHeight});
//    playButton.setFillColor(buttonColor);
//    playButton.setOrigin(buttonWidth / 2.0f, buttonHeight / 2.0f);
//    playButton.setPosition(centerX, window.getSize().y / 2.0f);
//
//    playButtonText.setFont(font);
//    playButtonText.setString("New Game");
//    playButtonText.setCharacterSize(charSize);
//    playButtonText.setFillColor(textColor);
//    centerTextOrigin(playButtonText);
//    playButtonText.setPosition(playButton.getPosition());
//
//    exitButton = playButton;
//    exitButton.setPosition(centerX, playButton.getPosition().y + 70.f);
//    exitButtonText = playButtonText;
//    exitButtonText.setString("Exit");
//    centerTextOrigin(exitButtonText);
//    exitButtonText.setPosition(exitButton.getPosition());
//
//    //Меню паузи
//    pauseTitleText = menuTitleText;
//    pauseTitleText.setString("Paused");
//    centerTextOrigin(pauseTitleText);
//    pauseTitleText.setPosition(centerX, window.getSize().y / 4.0f);
//
//    resumeButton = playButton;
//    resumeButton.setPosition(centerX, window.getSize().y / 2.0f);
//    resumeButtonText = playButtonText;
//    resumeButtonText.setString("Resume");
//    centerTextOrigin(resumeButtonText);
//    resumeButtonText.setPosition(resumeButton.getPosition());
//
//    pauseExitButton = exitButton;
//    pauseExitButton.setPosition(centerX, resumeButton.getPosition().y + 70.f);
//    pauseExitButtonText = exitButtonText;
//    pauseExitButtonText.setString("Main Menu");
//    centerTextOrigin(pauseExitButtonText);
//    pauseExitButtonText.setPosition(pauseExitButton.getPosition());
//
//    //Екран кінця гри
//    gameOverTitleText = menuTitleText;
//    gameOverTitleText.setString("Game Over");
//    centerTextOrigin(gameOverTitleText);
//    gameOverTitleText.setPosition(centerX, window.getSize().y / 4.0f);
//
//    finalScoreText.setFont(font);
//    finalScoreText.setCharacterSize(charSize);
//    finalScoreText.setFillColor(textColor);
//
//
//    restartButton = playButton;
//    restartButton.setPosition(centerX, window.getSize().y / 2.0f + 30.f);
//    restartButtonText = playButtonText;
//    restartButtonText.setString("Restart");
//    centerTextOrigin(restartButtonText);
//    restartButtonText.setPosition(restartButton.getPosition());
//
//    gameOverExitButton = exitButton;
//    gameOverExitButton.setPosition(centerX, restartButton.getPosition().y + 70.f);
//    gameOverExitButtonText = pauseExitButtonText;
//    gameOverExitButtonText.setPosition(gameOverExitButton.getPosition());
//
//    //Ігровий HUD
//    healthText.setFont(font);
//    healthText.setCharacterSize(18);
//    healthText.setFillColor(textColor);
//    healthText.setPosition(10.f, 10.f);
//
//    scoreText.setFont(font);
//    scoreText.setCharacterSize(18);
//    scoreText.setFillColor(textColor);
//    scoreText.setPosition(10.f, 30.f);
//}
//
//// Скидання гри до початкового стану
//void Game::resetGame() {
//    player.reset(1, 1);  player.reset(1, 1);
//    player.chooseWeapon(1);
//    enemies.clear();
//    enemies.add(make_unique<Zombie>("Zombie 1", 50, 10, 5, 5));
//    enemies.add(make_unique<Zombie>("Zombie 2", 60, 15, 10, 3));
//    enemies.add(make_unique<Boss>("BOSS", 120, 20, 10, 7, 7));
//    isPlayerTurn = true;
//    logMessages.clear();
//    addLogMessage("Game started!");
//    currentState = GameState::Playing;
//}
//
////Головний цикл та обробники
//
//void Game::runGameLoop() {
//    while (window.isOpen()) {
//        processEvents();
//        update();
//        render();
//    }
//}
//
//void Game::processEvents() {
//    sf::Event event;
//    while (window.pollEvent(event)) {
//        if (event.type == sf::Event::Closed) {
//            window.close();
//        }
//
//
//        switch (currentState) {
//            case GameState::MainMenu: processMainMenuEvents(event); break;
//            case GameState::Playing:  processPlayingEvents(event);  break;
//            case GameState::Paused:   processPausedEvents(event);   break;
//            case GameState::GameOver: processGameOverEvents(event); break;
//        }
//    }
//}
//
//void Game::update() {
//
//    if (currentState == GameState::Playing) {
//        updatePlaying();
//    }
//}
//
//void Game::render() {
//    window.clear(sf::Color::Black);
//
//
//    switch (currentState) {
//        case GameState::MainMenu: renderMainMenu(); break;
//        case GameState::Playing:  renderPlaying();  break;
//        case GameState::Paused:   renderPaused();   break;
//        case GameState::GameOver: renderGameOver(); break;
//    }
//
//    window.display();
//}
//
////Обробники подій для станів
//
//void Game::processMainMenuEvents(sf::Event& event) {
//    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
//        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
//        if (playButton.getGlobalBounds().contains(mousePos)) {
//            resetGame();
//        }
//        if (exitButton.getGlobalBounds().contains(mousePos)) {
//            window.close();
//        }
//    }
//}
//
//void Game::processPlayingEvents(sf::Event& event) {
//    if (isPlayerTurn && event.type == sf::Event::KeyPressed) {
//        bool actionTaken = false;
//        if (event.key.code == sf::Keyboard::W) { player.move(0, -1, map.getGrid()); actionTaken = true; }
//        if (event.key.code == sf::Keyboard::S) { player.move(0, 1, map.getGrid()); actionTaken = true; }
//        if (event.key.code == sf::Keyboard::A) { player.move(-1, 0, map.getGrid()); actionTaken = true; }
//        if (event.key.code == sf::Keyboard::D) { player.move(1, 0, map.getGrid()); actionTaken = true; }
//        if (event.key.code == sf::Keyboard::F) { handlePlayerAttack(); actionTaken = true; }
//        if (event.key.code == sf::Keyboard::Escape) { currentState = GameState::Paused; }
//
//        if (actionTaken && player.isAlive()) {
//            isPlayerTurn = false;
//        }
//    }
//}
//
//void Game::processPausedEvents(sf::Event& event) {
//    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
//        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
//        if (resumeButton.getGlobalBounds().contains(mousePos)) {
//            currentState = GameState::Playing;
//        }
//        if (pauseExitButton.getGlobalBounds().contains(mousePos)) {
//            currentState = GameState::MainMenu;
//        }
//    }
//
//    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
//        currentState = GameState::Playing;
//    }
//}
//
//void Game::processGameOverEvents(sf::Event& event) {
//    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
//        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
//        if (restartButton.getGlobalBounds().contains(mousePos)) {
//            resetGame();
//        }
//        if (gameOverExitButton.getGlobalBounds().contains(mousePos)) {
//            currentState = GameState::MainMenu;
//        }
//    }
//}
//
////Оновлення логіки гри
//void Game::centerTextOrigin(sf::Text& text) {
//    sf::FloatRect bounds = text.getLocalBounds();
//    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
//}
//
//void Game::updatePlaying() {
//    if (!isPlayerTurn && player.isAlive()) {
//        addLogMessage("Enemy turn.");
//        for (auto* e : enemies.getAllRaw()) {
//            if (auto* z = dynamic_cast<Zombie*>(e)) {
//                int dx = abs(z->getX() - player.getX());
//                int dy = abs(z->getY() - player.getY());
//                if (dx + dy == 1) {
//                    z->attack(player);
//
//                    if (!player.isAlive()) {
//                        addLogMessage("Player has fallen!");
//                        currentState = GameState::GameOver;
//                        gameOverTitleText.setString("Defeat...");
//                        centerTextOrigin(gameOverTitleText);
//                        break;
//                    }
//                }
//            }
//
//            if (currentState == GameState::GameOver) break;
//        }
//        isPlayerTurn = true;
//    }
//
//    //Перевірка умови перемоги (винесено з циклу ворогів)
//    if (currentState == GameState::Playing && enemies.size() == 0) {
//        currentState = GameState::GameOver;
//        gameOverTitleText.setString("Victory!");
//        centerTextOrigin(gameOverTitleText);
//        addLogMessage("All enemies defeated!");
//    }
//
//    //Оновлення HUD
//    healthText.setString("Health: " + std::to_string(player.getHealth()));
//    scoreText.setString("Score: " + std::to_string(player.getScore()));
//}
//
////Методи рендерингу для станів
//
//void Game::renderMainMenu() {
//    window.draw(menuTitleText);
//    window.draw(playButton);
//    window.draw(playButtonText);
//    window.draw(exitButton);
//    window.draw(exitButtonText);
//}
//
//void Game::renderPlaying() {
//    const int TILE_SIZE = 32;
//
//    //Малюємо карту
//    for (int y = 0; y < 15; ++y) {
//        for (int x = 0; x < 15; ++x) {
//            sf::Sprite tileSprite;
//            tileSprite.setTexture((map.getGrid()[y][x] == 1) ? wallTexture : floorTexture);
//            tileSprite.setPosition(static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE));
//            window.draw(tileSprite);
//        }
//    }
//
//    //Малюємо ворогів
//    for (auto* e : enemies.getAllRaw()) {
//        if (auto* z = dynamic_cast<Zombie*>(e)) {
//            sf::Sprite enemySprite;
//            enemySprite.setTexture(dynamic_cast<Boss*>(z) ? bossTexture : zombieTexture);
//            enemySprite.setPosition(static_cast<float>(z->getX() * TILE_SIZE), static_cast<float>(z->getY() * TILE_SIZE));
//            window.draw(enemySprite);
//        }
//    }
//
//    //Малюємо гравця
//    sf::Sprite playerSprite(playerTexture);
//    playerSprite.setPosition(static_cast<float>(player.getX() * TILE_SIZE), static_cast<float>(player.getY() * TILE_SIZE));
//    window.draw(playerSprite);
//
//    //Малюємо HUD
//    window.draw(healthText);
//    window.draw(scoreText);
//
//    //Малюємо ігровий лог
//    float logY = window.getSize().y - 20.f;
//    for (auto it = logMessages.rbegin(); it != logMessages.rend(); ++it) {
//        it->setPosition(10.f, logY);
//        window.draw(*it);
//        logY -= 20.f;
//    }
//}
//
//void Game::renderPaused() {
//    renderPlaying(); //Малюємо ігровий екран затемненим
//
//    //Малюємо напівпрозорий прямокутник зверху
//    sf::RectangleShape overlay({(float)window.getSize().x, (float)window.getSize().y});
//    overlay.setFillColor(sf::Color(0, 0, 0, 150));
//    window.draw(overlay);
//
//    //Малюємо елементи меню паузи
//    window.draw(pauseTitleText);
//    window.draw(resumeButton);
//    window.draw(resumeButtonText);
//    window.draw(pauseExitButton);
//    window.draw(pauseExitButtonText);
//}
//
//void Game::renderGameOver() {
//
//    finalScoreText.setString("Final Score: " + std::to_string(player.getScore()));
//    centerTextOrigin(finalScoreText);
//    finalScoreText.setPosition(window.getSize().x / 2.0f, gameOverTitleText.getPosition().y + 70.f);
//
//    //Малюємо елементи екрану кінця гри
//    window.draw(gameOverTitleText);
//    window.draw(finalScoreText);
//    window.draw(restartButton);
//    window.draw(restartButtonText);
//    window.draw(gameOverExitButton);
//    window.draw(gameOverExitButtonText);
//}
//
//
//
//void Game::handlePlayerAttack() {
//    bool attacked = false;
//    for (size_t i = 0; i < enemies.size(); ++i) {
//        if (auto* z = dynamic_cast<Zombie*>(enemies.get(i))) {
//            int dx = abs(z->getX() - player.getX());
//            int dy = abs(z->getY() - player.getY());
//            if (dx + dy == 1) {
//                player.attack(*z);
//                if (!player.isAlive()) {
//                    addLogMessage("Player has fallen!");
//                    currentState = GameState::GameOver;
//                    gameOverTitleText.setString("Defeat...");
//                    centerTextOrigin(gameOverTitleText);
//                    break;
//                }
//                attacked = true;
//                if (!z->isAlive()) {
//                    addLogMessage(z->getName() + " defeated!");
//                    player.addScore(50);
//                    enemies.remove(i);
//                }
//                break;
//            }
//        }
//    }
//    if (!attacked) {
//        addLogMessage("No enemy in range!");
//    }
//}
//
//void Game::addLogMessage(const std::string& message) {
//    if (logMessages.size() >= MAX_LOG_MESSAGES) {
//        logMessages.pop_front();
//    }
//    sf::Text newLog;
//    newLog.setFont(font);
//    newLog.setString(message);
//    newLog.setCharacterSize(14);
//    newLog.setFillColor(sf::Color::White);
//    logMessages.push_back(newLog);
//}
#include "Game.h"
// #include "Command.h" // Command більше не потрібен тут напряму
#include "Zombie.h"
#include "Boss.h"
#include <iostream>
#include <string> // Для std::to_string
#include <SFML/Graphics.hpp>
// --- Конструктор та налаштування ---

Game::Game(sf::RenderWindow& win)
    : window(win),
      currentState(GameState::MainMenu),
      player("Player", 100, 20, 1, 1), // Ініціалізуємо тут
      map(15, 15, 20)
{
    loadAssets();
    setupUI();
    // resetGame() більше не потрібен у конструкторі, бо гра починається з меню
}

Game::~Game() = default;

void Game::loadAssets() {
    if (!font.loadFromFile("arial.ttf")) { std::cout << "Error: Could not load font 'arial.ttf'" << std::endl; }
    if (!playerTexture.loadFromFile("player.png")) { std::cout << "Error loading player.png" << std::endl; }
    if (!zombieTexture.loadFromFile("zombie.png")) { std::cout << "Error loading zombie.png" << std::endl; }
    if (!bossTexture.loadFromFile("boss.png"))   { std::cout << "Error loading boss.png" << std::endl; }
    if (!wallTexture.loadFromFile("wall.png"))     { std::cout << "Error loading wall.png" << std::endl; }
    if (!floorTexture.loadFromFile("floor.png"))   { std::cout << "Error loading floor.png" << std::endl; }
}

// Допоміжний метод (визначення)
void Game::centerTextOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

void Game::setupUI() {
    float centerX = window.getSize().x / 2.0f;
    float buttonWidth = 200.f;
    float buttonHeight = 50.f;
    sf::Color buttonColor(100, 100, 100);
    sf::Color textColor = sf::Color::White;
    unsigned int charSize = 24;
    unsigned int titleCharSize = 50;

    // --- Головне меню ---
    menuTitleText.setFont(font);
    menuTitleText.setString("Zombie Survival");
    menuTitleText.setCharacterSize(titleCharSize);
    menuTitleText.setFillColor(textColor);
    centerTextOrigin(menuTitleText);
    menuTitleText.setPosition(centerX, window.getSize().y / 4.0f);

    playButton.setSize({buttonWidth, buttonHeight});
    playButton.setFillColor(buttonColor);
    playButton.setOrigin(buttonWidth / 2.0f, buttonHeight / 2.0f);
    playButton.setPosition(centerX, window.getSize().y / 2.0f);

    playButtonText.setFont(font);
    playButtonText.setString("New Game");
    playButtonText.setCharacterSize(charSize);
    playButtonText.setFillColor(textColor);
    centerTextOrigin(playButtonText);
    playButtonText.setPosition(playButton.getPosition());

    exitButton = playButton; // Копіюємо
    exitButton.setPosition(centerX, playButton.getPosition().y + 70.f);
    exitButtonText = playButtonText;
    exitButtonText.setString("Exit");
    centerTextOrigin(exitButtonText); // Перецентруємо текст "Exit"
    exitButtonText.setPosition(exitButton.getPosition());

    // --- Меню паузи ---
    pauseTitleText = menuTitleText; // Копіюємо стиль
    pauseTitleText.setString("Paused");
    centerTextOrigin(pauseTitleText);
    pauseTitleText.setPosition(centerX, window.getSize().y / 4.0f);

    resumeButton = playButton; // Копіюємо стиль
    resumeButton.setPosition(centerX, window.getSize().y / 2.0f);
    resumeButtonText = playButtonText;
    resumeButtonText.setString("Resume");
    centerTextOrigin(resumeButtonText);
    resumeButtonText.setPosition(resumeButton.getPosition());

    pauseExitButton = exitButton; // Копіюємо стиль
    pauseExitButton.setPosition(centerX, resumeButton.getPosition().y + 70.f);
    pauseExitButtonText = exitButtonText;
    pauseExitButtonText.setString("Main Menu");
    centerTextOrigin(pauseExitButtonText);
    pauseExitButtonText.setPosition(pauseExitButton.getPosition());

    // --- Екран кінця гри ---
    gameOverTitleText = menuTitleText; // Копіюємо стиль
    gameOverTitleText.setString("Game Over"); // Буде змінено на "Перемога" за потреби
    centerTextOrigin(gameOverTitleText);
    gameOverTitleText.setPosition(centerX, window.getSize().y / 4.0f);

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(charSize);
    finalScoreText.setFillColor(textColor);
    // Позиція буде встановлена пізніше

    restartButton = playButton; // Копіюємо стиль
    restartButton.setPosition(centerX, window.getSize().y / 2.0f + 30.f); // Трохи нижче
    restartButtonText = playButtonText;
    restartButtonText.setString("Restart");
    centerTextOrigin(restartButtonText);
    restartButtonText.setPosition(restartButton.getPosition());

    gameOverExitButton = exitButton; // Копіюємо стиль
    gameOverExitButton.setPosition(centerX, restartButton.getPosition().y + 70.f);
    gameOverExitButtonText = pauseExitButtonText; // Текст "Main Menu"
    gameOverExitButtonText.setPosition(gameOverExitButton.getPosition());

    // --- Ігровий HUD ---
    healthText.setFont(font);
    healthText.setCharacterSize(18);
    healthText.setFillColor(textColor);
    healthText.setPosition(10.f, 10.f); // Верхній лівий кут

    scoreText.setFont(font);
    scoreText.setCharacterSize(18);
    scoreText.setFillColor(textColor);
    scoreText.setPosition(10.f, 30.f); // Під здоров'ям
}

// Скидання гри до початкового стану
void Game::resetGame() {
    player.reset(1, 1); // <-- ВИПРАВЛЕНО: Скидаємо стан існуючого гравця
    player.chooseWeapon(1); // Даємо зброю заново
    enemies.clear(); // <-- ВИПРАВЛЕНО: Тепер Container має метод clear
    enemies.add(make_unique<Zombie>("Zombie 1", 50, 10, 5, 5));
    enemies.add(make_unique<Zombie>("Zombie 2", 60, 15, 10, 3));
    enemies.add(make_unique<Boss>("BOSS", 120, 20, 10, 7, 7));
    isPlayerTurn = true;
    logMessages.clear();
    addLogMessage("Game started!");
    currentState = GameState::Playing; // Переходимо в стан гри
}

// --- Головний цикл та обробники ---

void Game::runGameLoop() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        switch (currentState) {
            case GameState::MainMenu: processMainMenuEvents(event); break;
            case GameState::Playing:  processPlayingEvents(event);  break;
            case GameState::Paused:   processPausedEvents(event);   break;
            case GameState::GameOver: processGameOverEvents(event); break;
        }
    }
}

void Game::update() {
    if (currentState == GameState::Playing) {
        updatePlaying();
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    switch (currentState) {
        case GameState::MainMenu: renderMainMenu(); break;
        case GameState::Playing:  renderPlaying();  break;
        case GameState::Paused:   renderPaused();   break;
        case GameState::GameOver: renderGameOver(); break;
    }
    window.display();
}

// --- Обробники подій для станів ---

void Game::processMainMenuEvents(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (playButton.getGlobalBounds().contains(mousePos)) {
            resetGame(); // Скидаємо гру і переходимо в стан Playing
        }
        if (exitButton.getGlobalBounds().contains(mousePos)) {
            window.close();
        }
    }
}

void Game::processPlayingEvents(sf::Event& event) {
    if (isPlayerTurn && event.type == sf::Event::KeyPressed) {
        bool actionTaken = false;
        if (event.key.code == sf::Keyboard::W) { player.move(0, -1, map.getGrid()); actionTaken = true; }
        if (event.key.code == sf::Keyboard::S) { player.move(0, 1, map.getGrid()); actionTaken = true; }
        if (event.key.code == sf::Keyboard::A) { player.move(-1, 0, map.getGrid()); actionTaken = true; }
        if (event.key.code == sf::Keyboard::D) { player.move(1, 0, map.getGrid()); actionTaken = true; }
        if (event.key.code == sf::Keyboard::F) { handlePlayerAttack(); actionTaken = true; }
        if (event.key.code == sf::Keyboard::Escape) { currentState = GameState::Paused; }

        if (actionTaken && player.isAlive()) {
            isPlayerTurn = false;
        }
    }
}

void Game::processPausedEvents(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (resumeButton.getGlobalBounds().contains(mousePos)) {
            currentState = GameState::Playing;
        }
        if (pauseExitButton.getGlobalBounds().contains(mousePos)) {
            currentState = GameState::MainMenu;
        }
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentState = GameState::Playing;
    }
}

void Game::processGameOverEvents(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (restartButton.getGlobalBounds().contains(mousePos)) {
            resetGame();
        }
        if (gameOverExitButton.getGlobalBounds().contains(mousePos)) {
            currentState = GameState::MainMenu;
        }
    }
}

// --- Оновлення логіки гри ---

void Game::updatePlaying() {
    if (!isPlayerTurn && player.isAlive()) {
        addLogMessage("Enemy turn.");
        for (auto* e : enemies.getAllRaw()) {
            // Перевіряємо, чи гра не закінчилась після попереднього ворога
            if (currentState == GameState::GameOver) break;

            if (auto* z = dynamic_cast<Zombie*>(e)) {
                int dx = abs(z->getX() - player.getX());
                int dy = abs(z->getY() - player.getY());
                if (dx + dy == 1) { // Якщо ворог поруч
                    addLogMessage(z->getName() + " attacks Player."); // Логуємо перед атакою
                    z->attack(player); // <-- ВИПРАВЛЕНО: Просто викликаємо атаку
                    if (!player.isAlive()) {
                        addLogMessage("Player has fallen!");
                        currentState = GameState::GameOver;
                        gameOverTitleText.setString("Defeat...");
                        centerTextOrigin(gameOverTitleText);
                        break; // Виходимо з циклу ворогів
                    }
                }
            }
        }
        // Повертаємо хід гравцю тільки якщо гра не закінчилась
        if (currentState != GameState::GameOver) {
             isPlayerTurn = true;
        }
    }

    // Перевірка умови перемоги
    if (currentState == GameState::Playing && enemies.size() == 0) {
        currentState = GameState::GameOver;
        gameOverTitleText.setString("Victory!");
        centerTextOrigin(gameOverTitleText);
        addLogMessage("All enemies defeated!");
    }

    // Оновлення HUD
    healthText.setString("Health: " + std::to_string(player.getHealth()));
    scoreText.setString("Score: " + std::to_string(player.getScore()));
}

// --- Методи рендерингу для станів ---

void Game::renderMainMenu() {
    window.draw(menuTitleText);
    window.draw(playButton);
    window.draw(playButtonText);
    window.draw(exitButton);
    window.draw(exitButtonText);
}

void Game::renderPlaying() {
    const int TILE_SIZE = 32;

    for (int y = 0; y < 15; ++y) {
        for (int x = 0; x < 15; ++x) {
            sf::Sprite tileSprite;
            tileSprite.setTexture((map.getGrid()[y][x] == 1) ? wallTexture : floorTexture);
            tileSprite.setPosition(static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE));
            window.draw(tileSprite);
        }
    }
    for (auto* e : enemies.getAllRaw()) {
        if (auto* z = dynamic_cast<Zombie*>(e)) {
            sf::Sprite enemySprite;
            enemySprite.setTexture(dynamic_cast<Boss*>(z) ? bossTexture : zombieTexture);
            enemySprite.setPosition(static_cast<float>(z->getX() * TILE_SIZE), static_cast<float>(z->getY() * TILE_SIZE));
            window.draw(enemySprite);
        }
    }
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setPosition(static_cast<float>(player.getX() * TILE_SIZE), static_cast<float>(player.getY() * TILE_SIZE));
    window.draw(playerSprite);
    window.draw(healthText);
    window.draw(scoreText);

    float logY = window.getSize().y - 20.f;
    for (auto it = logMessages.rbegin(); it != logMessages.rend(); ++it) {
        it->setPosition(10.f, logY);
        window.draw(*it);
        logY -= 20.f;
    }
}

void Game::renderPaused() {
    renderPlaying(); // Малюємо гру на фоні

    sf::RectangleShape overlay({(float)window.getSize().x, (float)window.getSize().y});
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    window.draw(pauseTitleText);
    window.draw(resumeButton);
    window.draw(resumeButtonText);
    window.draw(pauseExitButton);
    window.draw(pauseExitButtonText);
}

void Game::renderGameOver() {
    finalScoreText.setString("Final Score: " + std::to_string(player.getScore()));
    centerTextOrigin(finalScoreText);
    finalScoreText.setPosition(window.getSize().x / 2.0f, gameOverTitleText.getPosition().y + 70.f);

    window.draw(gameOverTitleText);
    window.draw(finalScoreText);
    window.draw(restartButton);
    window.draw(restartButtonText);
    window.draw(gameOverExitButton);
    window.draw(gameOverExitButtonText);
}

// --- Допоміжні методи ---

void Game::handlePlayerAttack() {
    bool attacked = false;
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (auto* z = dynamic_cast<Zombie*>(enemies.get(i))) {
            int dx = abs(z->getX() - player.getX());
            int dy = abs(z->getY() - player.getY());
            if (dx + dy == 1) {
                addLogMessage("Player attacks " + z->getName() + "."); // Логуємо перед атакою
                player.attack(*z); // <-- ВИПРАВЛЕНО: Просто викликаємо атаку
                attacked = true;
                if (!z->isAlive()) {
                    addLogMessage(z->getName() + " defeated!");
                    player.addScore(50);
                    enemies.remove(i);
                    // Важливо: зменшуємо i, оскільки вектор зсунувся
                    i--; // Або просто виходимо з циклу, якщо атакуємо одного
                    break; // Атакуємо лише одного ворога
                }
                break; // Атакуємо лише одного ворога
            }
        }
    }
    if (!attacked) {
        addLogMessage("No enemy in range!");
    }
}

void Game::addLogMessage(const std::string& message) {
    if (logMessages.size() >= MAX_LOG_MESSAGES) {
        logMessages.pop_front();
    }
    sf::Text newLog;
    newLog.setFont(font);
    newLog.setString(message);
    newLog.setCharacterSize(14);
    newLog.setFillColor(sf::Color::White);
    logMessages.push_back(newLog);
}