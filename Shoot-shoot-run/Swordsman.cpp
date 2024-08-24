#include "Swordsman.h"

Swordsman::Swordsman(const sf::Vector2f& startPos, const sf::Vector2f* screenPos) :
  Enemy(startPos, screenPos, { GameEvent::EventType::None })
{
  triangle.setOrigin(sf::Vector2f(sgs::SIZE_SWORDSMAN, sgs::SIZE_SWORDSMAN));
  triangle.setFillColor(sf::Color::Black);
}

void Swordsman::update(const sf::Vector2f& heroPos) {
  newEvent = { GameEvent::EventType::None };

  if (standingTicks > 0) {
    standingTicks -= 1;
    triangle.setPosition(pos - *screenPos);
    triangle.setRotation(210 - facingAngle);
    return;
  }

  sf::Vector2f movVector = heroPos - pos;

  facingAngle = (atan(-movVector.y / movVector.x)) * (180 / sgs::PI);
  if (movVector.x < 0)
    facingAngle = 180 + facingAngle;

  triangle.setRotation(210 - facingAngle);

  float length = sqrt(movVector.x * movVector.x + movVector.y * movVector.y);
  if (length < sgs::SWORDSMAN_ATTACK_RADIUS) {
    newEvent = { GameEvent::EventType::SwordAttack };
    standingTicks = sgs::SWORDSMAN_ATTACK_SPEED;
  }

  movVector /= length;

  speed = movVector * sgs::SPEED_SWORDSMAN;

  pos += speed;

  triangle.setPosition(pos - *screenPos);
  triangle.setRotation(210 - facingAngle);
}

bool Swordsman::touchesPoint(const sf::Vector2f& pt) {
  return false;
}

GameEvent Swordsman::getNewEvent() {
  GameEvent temp = newEvent;
  newEvent = { GameEvent::EventType::None };
  return temp;
}

float Swordsman::getAngle() {
  return 90 - facingAngle;
}

const sf::Drawable& Swordsman::getSprite() {
  return triangle;
}
