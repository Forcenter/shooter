#ifndef BULLET_H
#define BULLET_H

#include "SFML/Graphics.hpp"
#include "constants.h"

class Bullet {
private:
  sf::RectangleShape body;
  sf::Vector2f pos;
  float facingAngle;
  const sf::Vector2f* screenPos;
public:
  Bullet(const sf::Vector2f& pos, float facingAngle, const sf::Vector2f* screenPos);

  std::pair< sf::Vector2f, sf::Vector2f > getHitbox();

  void update();

  const sf::Drawable& getSprite();
};

#endif