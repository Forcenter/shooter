#ifndef HERO_H
#define HERO_H

#include "SFML/Graphics.hpp"
#include "constants.h"

#include <iostream>
namespace sgs {
  class Hero {
  private:
    sf::Vector2f pos;
    sf::Vector2f speed;
    const sf::Vector2f* screenPos;
    sf::CircleShape triangle = sf::CircleShape(sgs::SIZE_HERO, 3);

    std::pair< sgs::direction, bool > whereToMove[4];

    float facingAngle;
    int shootingCountdown = -1;

  public:
    Hero();

    void setPos(float, float);
    void setScreen(const sf::Vector2f* pos);

    void lookAt(const sf::Vector2i& pos);

    sf::Vector2f getPosition();
    float getFacingAngle();

    void beginGoForward();
    void stopGoForward();
    void beginGoBack();
    void stopGoBack();
    void beginGoLeft();
    void stopGoLeft();
    void beginGoRight();
    void stopGoRight();
    void beginShooting();
    void stopShooting();

    bool isFiring();

    bool damageBullet(sf::Vector2f&);

    void update();

    const sf::Drawable& getSprite();
  };
}

#endif