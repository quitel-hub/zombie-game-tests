#include "gtest/gtest.h"
#include "../Player.h"
#include "../Zombie.h"
#include "../Boss.h"
#include "../Map.h"
#include "../Container.h"
#include <vector>

// Тест 1: Перевірка правильного розрахунку шкоди for player
TEST(CombatLogic, PlayerDealsCorrectDamageWithSword) {
    Player player("Hero", 100, 20, 1, 1);
    player.chooseWeapon(1); // Меч, шкода 40
    Zombie zombie("Target", 80, 10, 1, 2);
    int expectedHealth = 80 - (20 + 40);

    player.attack(zombie);

    ASSERT_EQ(zombie.getHealth(), expectedHealth);
}

// Тест 2: Перевірка, що entity помирає від летальної шкоди
TEST(CombatLogic, EntityDiesFromFatalDamage) {
    Zombie zombie("Target", 50, 10, 1, 2);
    zombie.takeDamage(100);

    ASSERT_EQ(zombie.getHealth(), 0);
    ASSERT_FALSE(zombie.isAlive());
}

// Тест 3: Перевірка коректного переміщення player на порожню клітинку
TEST(MovementLogic, PlayerMovesToEmptyCell) {
    Player player("Hero", 100, 20, 1, 1);
    Map map(5, 5, 0);

    player.move(1, 0, map.getGrid());

    ASSERT_EQ(player.getX(), 2);
    ASSERT_EQ(player.getY(), 1);
}

// Тест 4: Перевірка, що player не може рухатись у стіну
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


// Тест 5: Перевірка отримання точної летальної damage
TEST(CombatLogic, EntityDiesFromExactFatalDamage) {
    Zombie zombie("Target", 50, 10, 1, 2);
    zombie.takeDamage(50);

    ASSERT_EQ(zombie.getHealth(), 0);
    ASSERT_FALSE(zombie.isAlive());
}

// Тест 6: Перевірка, що health не стає негативним
TEST(CombatLogic, HealthDoesNotBecomeNegative) {
    Zombie zombie("Target", 10, 10, 1, 2);
    zombie.takeDamage(100);

    ASSERT_EQ(zombie.getHealth(), 0);
}

// Тест 7: Перевірка атаки Boss з урахуванням rage
TEST(CombatLogic, BossDealsCorrectDamageWithRage) {
    Player player("Hero", 100, 10, 1, 1);
    Boss boss("BigBoss", 200, 30, 15, 1, 2);
    int expectedHealth = 100 - (30 + 15); // 100 - 45 = 55

    boss.attack(player);

    ASSERT_EQ(player.getHealth(), expectedHealth);
}

// Тест 8: Перевірка атаки Zombie без rage
TEST(CombatLogic, ZombieDealsCorrectDamage) {
    Player player("Hero", 100, 10, 1, 1);
    Zombie zombie("Walker", 50, 10, 1, 2);
    int expectedHealth = 100 - 10; // 100 - 10 = 90

    zombie.attack(player);

    ASSERT_EQ(player.getHealth(), expectedHealth);
}

// Тест 9: Перевірка вибору другої weapon (gun)
TEST(PlayerLogic, PlayerChoosesGun) {
    Player player("Hero", 100, 20, 1, 1);
    player.chooseWeapon(2); // Пістолет, шкода 25
    Zombie zombie("Target", 80, 10, 1, 2);
    int expectedHealth = 80 - (20 + 25); // 80 - 45 = 35

    player.attack(zombie);

    ASSERT_EQ(zombie.getHealth(), expectedHealth);
}

// Тест 10: Перевірка вибору weapon за замовчуванням при невірному вводі
TEST(PlayerLogic, PlayerGetsDefaultWeaponOnInvalidChoice) {
    Player player("Hero", 100, 20, 1, 1);
    player.chooseWeapon(99);
    Zombie zombie("Target", 80, 10, 1, 2);
    int expectedHealth = 80 - (20 + 40); // 80 - 60 = 20

    player.attack(zombie);

    ASSERT_EQ(zombie.getHealth(), expectedHealth);
}

// Тест 11: Перевірка додавання очок for player
TEST(PlayerLogic, ScoreIncreasesCorrectly) {
    Player player("Hero", 100, 20, 1, 1);
    ASSERT_EQ(player.getScore(), 0);
    player.addScore(50);
    ASSERT_EQ(player.getScore(), 50);
    player.addScore(30);
    ASSERT_EQ(player.getScore(), 80);
}

// Тест 12: Перевірка, що player не може вийти за межі map вліво/вгору
TEST(MovementLogic, PlayerStaysWithinMapBoundsNegative) {
    Player player("Hero", 100, 20, 0, 0);
    Map map(5, 5, 0);

    player.move(-1, 0, map.getGrid());
    ASSERT_EQ(player.getX(), 0);
    ASSERT_EQ(player.getY(), 0);

    player.move(0, -1, map.getGrid());
    ASSERT_EQ(player.getX(), 0);
    ASSERT_EQ(player.getY(), 0);
}

// Тест 13: Перевірка, що player не може вийти за межі map вправо/вниз
TEST(MovementLogic, PlayerStaysWithinMapBoundsPositive) {
    Map map(5, 5, 0);
    Player player("Hero", 100, 20, 4, 4);

    player.move(1, 0, map.getGrid());
    ASSERT_EQ(player.getX(), 4);
    ASSERT_EQ(player.getY(), 4);

    player.move(0, 1, map.getGrid());
    ASSERT_EQ(player.getX(), 4);
    ASSERT_EQ(player.getY(), 4);
}

// Тест 14: Перевірка роботи контейнера: додавання та розмір
TEST(ContainerLogic, AddAndSize) {
    Container<Entity> container;
    ASSERT_EQ(container.size(), 0);
    container.add(make_unique<Zombie>("Z1", 10, 1, 0, 0));
    ASSERT_EQ(container.size(), 1);
    container.add(make_unique<Boss>("B1", 100, 10, 5, 0, 0));
    ASSERT_EQ(container.size(), 2);
}

// Тест 15: Перевірка роботи контейнера: отримання та видалення
TEST(ContainerLogic, GetAndRemove) {
    Container<Entity> container;
    container.add(make_unique<Zombie>("Z1", 10, 1, 0, 0));
    container.add(make_unique<Boss>("B1", 100, 10, 5, 0, 0));


    Entity* first = container.get(0);
    ASSERT_NE(first, nullptr);
    ASSERT_EQ(first->getName(), "Z1");

    Entity* second = container.get(1);
    ASSERT_NE(second, nullptr);
    ASSERT_EQ(second->getName(), "B1");

    Entity* outOfBounds = container.get(2);
    ASSERT_EQ(outOfBounds, nullptr);


    container.remove(0);
    ASSERT_EQ(container.size(), 1);
    Entity* nowFirst = container.get(0);
    ASSERT_NE(nowFirst, nullptr);
    ASSERT_EQ(nowFirst->getName(), "B1");
}