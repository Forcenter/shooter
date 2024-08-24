#include "SwordAttack.h"
#include "constants.h"

#include <iostream>

SwordAttack::SwordAttack(const sf::Vector2f& pos, float angle, const sf::Vector2f* screenPos):
  angle(angle),
  pos(pos),
  rect(),
  screenPos(screenPos)
{
  rect.setPosition(pos);
  rect.setFillColor(sf::Color::Black);
  rect.setSize({ sgs::SIZE_SWORDSMAN / 5, sgs::SWORDSMAN_ATTACK_RADIUS });
  rect.setOrigin({ sgs::SIZE_SWORDSMAN / 10, sgs::SIZE_SWORDSMAN + sgs::SWORDSMAN_ATTACK_RADIUS });
  rect.setRotation(angle);
}

void SwordAttack::update() {
  rect.setRotation(angle - DEGREE_ATTACK_WIDTH / 2 + DEGREE_ATTACK_WIDTH * static_cast< float >(state) / ANIMATION_PHASE_AMOUNT);
  ++state;
  rect.setPosition(pos - *screenPos);
}

bool SwordAttack::isTouching(const sf::Vector2f& point) {
  return false;
}

bool SwordAttack::isAlive() {
  return state != ANIMATION_PHASE_AMOUNT + 1;
}

const sf::Drawable& SwordAttack::getSprite() {
  return rect;
}
