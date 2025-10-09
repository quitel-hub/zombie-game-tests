#include "gtest/gtest.h"
#include "../Player.h"
#include "../Zombie.h"
#include "../Map.h"


TEST(CombatLogic, PlayerDealsCorrectDamage) {

Player player("Hero", 100, 20, 1, 1);
player.chooseWeapon(1); // Меч, шкода 40
Zombie zombie("Target", 80, 10, 1, 2);
int expectedHealth = 80 - (20 + 40);


player.attack(zombie);


ASSERT_EQ(zombie.getHealth(), expectedHealth);
}


TEST(CombatLogic, EntityDiesFromFatalDamage) {

Zombie zombie("Target", 50, 10, 1, 2);


zombie.takeDamage(100);


ASSERT_EQ(zombie.getHealth(), 0);
ASSERT_FALSE(zombie.isAlive());
}


TEST(MovementLogic, PlayerMovesToEmptyCell) {

Player player("Hero", 100, 20, 1, 1);
Map map(5, 5, 0);


player.move(1, 0, map.getGrid());


ASSERT_EQ(player.getX(), 2);
ASSERT_EQ(player.getY(), 1);
}


TEST(MovementLogic, PlayerCannotMoveIntoWall) {

Player player("Hero", 100, 20, 1, 1);
vector<vector<int>> grid = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
};

player.move(1, 0, grid);


ASSERT_EQ(player.getX(), 1);
ASSERT_EQ(player.getY(), 1);
}