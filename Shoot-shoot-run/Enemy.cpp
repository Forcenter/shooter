#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& startPos, const sf::Vector2f* screenPos, GameEvent e):
  pos(startPos),
  health(100),
  screenPos(screenPos),
  facingAngle(0),
  newEvent(e)
{}

sf::Vector2f& Enemy::getPosition() {
  return pos;
}

float Enemy::getAngle() {
    return facingAngle;
}
