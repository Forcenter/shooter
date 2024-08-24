#include "bullet.h"

#include <cmath>

Bullet::Bullet(const sf::Vector2f& pos, float facingAngle, const sf::Vector2f* screenPos):
  body(sgs::BULLET_SIZE),
  screenPos(screenPos),
  facingAngle((180 - facingAngle) * sgs::PI / 180),
  pos(pos)
{
  body.setOrigin(sf::Vector2f(sgs::BULLET_SIZE.x / 2, sgs::BULLET_SIZE.y / 2));
  body.setPosition(pos);
  body.setRotation(180 - facingAngle);
  body.setFillColor(sf::Color::Yellow);
}

std::pair<sf::Vector2f, sf::Vector2f> Bullet::getHitbox()
{
  std::pair<sf::Vector2f, sf::Vector2f> result;
  sf::Vector2f pos = body.getPosition();
  float facingAngle = body.getRotation() / 180 * sgs::PI;
  result.first = -sgs::BULLET_SIZE / 2.f;
  result.second = sgs::BULLET_SIZE / 2.f;
  sf::Vector2f temp = {
    result.first.x * sin(facingAngle) + result.first.y * -cos(facingAngle),
    result.first.x * cos(facingAngle) + result.first.y * sin(facingAngle),
  };
  result.first = pos + temp;
  temp = {
    result.second.x * sin(facingAngle) + result.second.y * -cos(facingAngle),
    result.second.x * cos(facingAngle) + result.second.y * sin(facingAngle),
  };
  result.second = pos + temp;
  return result;
}

void Bullet::update()
{
  pos.x -= sgs::BULLET_SPEED * cos(facingAngle);
  pos.y -= sgs::BULLET_SPEED * sin(facingAngle);
  body.setPosition(pos - *screenPos);
}

const sf::Drawable& Bullet::getSprite()
{
  return body;
}
