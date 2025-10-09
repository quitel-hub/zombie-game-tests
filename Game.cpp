#include "Game.h"
#include "Command.h"
#include "Zombie.h"
#include "Boss.h"
#include "LocalizationManager.h"

Game::Game()
        : player("Player", 100, 20, 1, 1),
          map(15, 15, 20)
{

    enemies.add(make_unique<Zombie>("Zombie 1", 50, 10, 5, 5));
    enemies.add(make_unique<Zombie>("Zombie 2", 60, 15, 10, 3));
    enemies.add(make_unique<Boss>("BOSS", 120, 20, 10, 7, 7));


    commands['w'] = make_unique<MoveCommand>(0, -1);
    commands['s'] = make_unique<MoveCommand>(0, 1);
    commands['a'] = make_unique<MoveCommand>(-1, 0);
    commands['d'] = make_unique<MoveCommand>(1, 0);
    commands['f'] = make_unique<AttackCommand>();
    commands['q'] = make_unique<QuitCommand>();
}


Game::~Game() = default;

void Game::run() {
    cout << L10N.getString("game_start") << endl;
    cout << L10N.getString("choose_weapon") << endl;
    int choice;
    cin >> choice;
    player.chooseWeapon(choice);

    while (player.isAlive() && enemies.size() > 0 && !isGameOver) {
        cout << L10N.getFormattedString("health_score_hud", player.getHealth(), player.getScore()) << endl;
        map.render(player, enemies.getAllRaw());

        cout << L10N.getString("player_turn_header") << endl;
        cout << L10N.getString("player_turn_prompt");
        char input;
        cin >> input;

        auto it = commands.find(tolower(input));
        if (it != commands.end()) {
            it->second->execute(*this);
        }

        if (isGameOver || !player.isAlive()) break;


        cout << L10N.getString("enemy_turn_header") << endl;
        for (auto* e : enemies.getAllRaw()) {
            if (auto* z = dynamic_cast<Zombie*>(e)) {
                int dx = abs(z->getX() - player.getX());
                int dy = abs(z->getY() - player.getY());
                if (dx + dy == 1) {
                    z->attack(player);
                    if (!player.isAlive()) break;
                }
            }
        }
    }

    if (player.isAlive() && enemies.size() == 0) {
        cout << L10N.getString("victory") << endl;
    } else {
        cout << L10N.getString("defeat") << endl;
    }
    cout << L10N.getFormattedString("final_score", player.getScore()) << endl;
}

void Game::handlePlayerAttack() {
    bool attacked = false;
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (auto* z = dynamic_cast<Zombie*>(enemies.get(i))) {
            int dx = abs(z->getX() - player.getX());
            int dy = abs(z->getY() - player.getY());
            if (dx + dy == 1) {
                player.attack(*z);
                attacked = true;
                if (!z->isAlive()) {
                    cout << L10N.getFormattedString("enemy_defeated", z->getName()) << endl;
                    player.addScore(50);
                    enemies.remove(i);
                }
                break;
            }
        }
    }
    if (!attacked) {
        cout << L10N.getString("no_enemy_in_range") << endl;
    }
}