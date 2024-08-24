#include "Block.h"

Block::Block(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Vector2f* screen) :
  rect(size),
  screenPos(screen),
  pos(pos)
{}

std::array<sf::Vector2f, 4> Block::getLightBasePoints() {
  std::array< sf::Vector2f, 4 > result;
  sf::Vector2f size = rect.getSize();
  result[0] = pos;
  result[1] = { pos.x + size.x, pos.y };
  result[2] = { pos.x, pos.y + size.y };
  result[3] = pos + size;
  return result;
}

void Block::update() {
  rect.setPosition(pos - *screenPos);
}

const sf::Drawable& Block::getSprite() {
  return rect;
}
