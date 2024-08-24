#ifndef BLOCK_H
#define BLOCK_H

#include "SFML/Graphics.hpp"
#include <array>

class Block {
private:
  sf::RectangleShape rect;

  sf::Vector2f pos;

  const sf::Vector2f* screenPos;

public:
  Block(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Vector2f* screen);

  std::array< sf::Vector2f, 4 > getLightBasePoints();

  void update();

  const sf::Drawable& getSprite();
};

#endif