#define _WIN32_WINNT 0x0A00
#define WIN32_LEAN_AND_MEAN

#include <SFML/Graphics.hpp>
#include <windows.h>
#include<cstdlib>
#include<iostream>
#include<string>
#include<ctime>
#include "Game.h"
#include "LocalizationManager.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Zombie Survival");
//    Game game;
//    while (window.isOpen()) {
//        // Обробка подій (натискання клавіш, закриття вікна)
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            // Тут буде обробка натискань клавіш
//        }
//        // Оновлення логіки гри
//        game.update();
//
//        // Очищення вікна
//        window.clear();
//
//        // Малювання ігрових об'єктів
//        game.render(window);
//
//        // Відображення намальованого на екрані
//        window.display();
//    }

    string lang;
    cout << "Choose language (en/ukr):";
    cin >> lang;

    if (!L10N.loadLanguage(lang)){
        L10N.loadLanguage("en");
    }


    srand(time(nullptr));
    Game g;
    g.run();
    return 0;
}