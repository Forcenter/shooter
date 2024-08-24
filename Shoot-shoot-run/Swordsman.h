#pragma once
#include "enemy.h"
#include "constants.h"

class Swordsman: public Enemy {
private:
  sf::CircleShape triangle = sf::CircleShape(sgs::SIZE_SWORDSMAN, 3);

  float standingTicks = 0;

public:
  Swordsman(const sf::Vector2f& startPos, const sf::Vector2f* screenPos);

  void update(const sf::Vector2f& heroPos) override;

  bool touchesPoint(const sf::Vector2f& pt) override;

  GameEvent getNewEvent() override;

  float getAngle() override;

  const sf::Drawable& getSprite() override;
};

