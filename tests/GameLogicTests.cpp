#include "gtest/gtest.h"
#include "../Player.h"
#include "../Zombie.h"
#include "../Boss.h"
#include "../Map.h"
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

// Тест 3: Перевірка отримання точної летальної damage
TEST(CombatLogic, EntityDiesFromExactFatalDamage) {
    Zombie zombie("Target", 50, 10, 1, 2);
    zombie.takeDamage(50);

    ASSERT_EQ(zombie.getHealth(), 0);
    ASSERT_FALSE(zombie.isAlive());
}

// Тест 4: Перевірка, що health не стає негативним
TEST(CombatLogic, HealthDoesNotBecomeNegative) {
    Zombie zombie("Target", 10, 10, 1, 2);
    zombie.takeDamage(100);

    ASSERT_EQ(zombie.getHealth(), 0);
}

// Тест 5: Перевірка атаки Boss з урахуванням rage
TEST(CombatLogic, BossDealsCorrectDamageWithRage) {
    Player player("Hero", 100, 10, 1, 1);
    Boss boss("BigBoss", 200, 30, 15, 1, 2);
    int expectedHealth = 100 - (30 + 15); // 100 - 45 = 55

    boss.attack(player);

    ASSERT_EQ(player.getHealth(), expectedHealth);
}

// Тест 6: Перевірка атаки Zombie без rage
TEST(CombatLogic, ZombieDealsCorrectDamage) {
    Player player("Hero", 100, 10, 1, 1);
    Zombie zombie("Walker", 50, 10, 1, 2);
    int expectedHealth = 100 - 10; // 100 - 10 = 90

    zombie.attack(player);

    ASSERT_EQ(player.getHealth(), expectedHealth);
}

// Тест 7: Перевірка вибору другої weapon (gun)
TEST(PlayerLogic, PlayerChoosesGun) {
    Player player("Hero", 100, 20, 1, 1);
    player.chooseWeapon(2); // Пістолет, шкода 25
    Zombie zombie("Target", 80, 10, 1, 2);
    int expectedHealth = 80 - (20 + 25); // 80 - 45 = 35

    player.attack(zombie);

    ASSERT_EQ(zombie.getHealth(), expectedHealth);
}

// Тест 8: Перевірка вибору weapon за замовчуванням при невірному вводі
TEST(PlayerLogic, PlayerGetsDefaultWeaponOnInvalidChoice) {
    Player player("Hero", 100, 20, 1, 1);
    player.chooseWeapon(99);
    Zombie zombie("Target", 80, 10, 1, 2);
    int expectedHealth = 80 - (20 + 40); // 80 - 60 = 20

    player.attack(zombie);

    ASSERT_EQ(zombie.getHealth(), expectedHealth);
}

// Тест 9: Перевірка додавання очок for player
TEST(PlayerLogic, ScoreIncreasesCorrectly) {
    Player player("Hero", 100, 20, 1, 1);
    ASSERT_EQ(player.getScore(), 0);
    player.addScore(50);
    ASSERT_EQ(player.getScore(), 50);
    player.addScore(30);
    ASSERT_EQ(player.getScore(), 80);
}

