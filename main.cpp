#include <cstdlib>
#include <ctime>
#include "Game.h"
using namespace std;


//int main() {
//    srand((unsigned)time(nullptr));
//    Game game;
//    game.run();
//    return 0;
//}
int main() {
    srand(time(nullptr));
    Game g;
    g.run();
    return 0;
}