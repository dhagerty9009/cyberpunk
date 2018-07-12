#include <stdio.h>
#include "main.hpp"

Destructible::Destructible(float maxHealth, float defense, const char *corpseName) : maxHealth(maxHealth), currentHealth(maxHealth), defense(defense), corpseName(corpseName) {}

float Destructible::takeDamage(Actor *owner, float damage)
{
  damage -= defense;
  if (damage > 0)
  {
    currentHealth -= damage;
    if (currentHealth <= 0)
    {
      die(owner);
    }
  }
  else
  {
    damage = 0;
  }
  return damage;
}

void Destructible::die(Actor *owner)
{
  owner->character = '%';
  owner->color = TCODColor::darkRed;
  owner->name = corpseName;
  owner->blocks = false;
  engine.sendToBack(owner);
}

MonsterDestructible::MonsterDestructible(float maxHealth, float defense, const char *corpseName) : Destructible(maxHealth, defense, corpseName)
{
}

PlayerDestructible::PlayerDestructible(float maxHealth, float defense, const char *corpseName) : Destructible(maxHealth, defense, corpseName)
{
}

void MonsterDestructible::die(Actor *owner)
{
  printf("%s is dead\n", owner->name);
  Destructible::die(owner);
}

void PlayerDestructible::die(Actor *owner)
{
  printf("You died!\n");
  Destructible::die(owner);
  engine.gameStatus = Engine::DEFEAT;
}