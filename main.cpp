// #define _WIN32_WINNT 0x0A00
// #define WIN32_LEAN_AND_MEAN
//
// #include <SFML/Graphics.hpp>
// #include <windows.h>
// #include<cstdlib>
// #include<iostream>
// #include<string>
// #include<ctime>
// #include "Game.h"
// #include "LocalizationManager.h"
//
// using namespace std;
//
// int main() {
//     SetConsoleOutputCP(CP_UTF8);
//     SetConsoleCP(CP_UTF8);
//     string lang;
//     cout << "Choose language (en/ukr):";
//     cin >> lang;
//
//     if (!L10N.loadLanguage(lang)){
//         L10N.loadLanguage("en");
//     }
//
//
//     srand(time(nullptr));
//     Game g;
//     g.run();
//     return 0;
// }
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Game.h"
#include "LocalizationManager.h"

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    //TODO: Можна зробити вибір мови частиною головного меню
    L10N.loadLanguage("ukr");

    //
    sf::RenderWindow window(sf::VideoMode(480, 480), "Zombie Survival");
    window.setFramerateLimit(60);

    Game game(window);
    game.runGameLoop();

    return 0;
}