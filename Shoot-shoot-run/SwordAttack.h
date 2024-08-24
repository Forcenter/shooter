#pragma once
#include "SFML/Graphics.hpp"

class SwordAttack {
private:
  sf::RectangleShape rect;
  float angle;

  int state = 0;

  sf::Vector2f pos;
  const sf::Vector2f* screenPos;

  static const int ANIMATION_PHASE_AMOUNT = 8;
  static const int DEGREE_ATTACK_WIDTH = 40;

public:
  SwordAttack(const sf::Vector2f& pos, float angle, const sf::Vector2f* screenPos);

  void update();

  bool isTouching(const sf::Vector2f& point);
  bool isAlive();

  const sf::Drawable& getSprite();
};
