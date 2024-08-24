#pragma once
#include "SFML/Graphics.hpp"
#include "gameEvent.h"

class Enemy {
protected:
  sf::Vector2f pos;
  sf::Vector2f speed;
  int health;
  const sf::Vector2f* screenPos;

  float facingAngle;

  GameEvent newEvent;

public:
  Enemy(const sf::Vector2f& startPos, const sf::Vector2f* screenPos, GameEvent e);


  virtual bool touchesPoint(const sf::Vector2f& point) = 0;

  virtual void update(const sf::Vector2f& heroPos) = 0;

  virtual GameEvent getNewEvent() = 0;

  sf::Vector2f& getPosition();

  virtual float getAngle();

  virtual const sf::Drawable& getSprite() = 0;
};
