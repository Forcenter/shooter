#include "Hero.h"
#include <cmath>

sgs::Hero::Hero():
  pos(0, 0),
  facingAngle(0)
{
  triangle.setFillColor(sf::Color::Red);
  triangle.setOrigin(sf::Vector2f(sgs::SIZE_HERO, sgs::SIZE_HERO));
}

void sgs::Hero::setPos(float x, float y) {
  pos = { x, y };
  triangle.setPosition(pos);
}

void sgs::Hero::setScreen(const sf::Vector2f* pos) {
  screenPos = pos;
}

void sgs::Hero::lookAt(const sf::Vector2i& at) {
  sf::Vector2f relPos = pos - *screenPos;
  facingAngle = (atan(-(at.y - relPos.y) / (at.x - relPos.x))) * (180 / sgs::PI);
  if (at.x < relPos.x)
    facingAngle = 180 + facingAngle;

  triangle.setRotation(210 - facingAngle);
}

sf::Vector2f sgs::Hero::getPosition() {
  return pos;
}

float sgs::Hero::getFacingAngle() {
  return facingAngle;
}

void sgs::Hero::beginGoForward() {
  whereToMove[sgs::direction::forward].second = true;
}
void sgs::Hero::stopGoForward() {
  whereToMove[sgs::direction::forward].second = false;
}
void sgs::Hero::beginGoBack() {
  whereToMove[sgs::direction::back].second = true;
}
void sgs::Hero::stopGoBack() {
  whereToMove[sgs::direction::back].second = false;
}
void sgs::Hero::beginGoLeft() {
  whereToMove[sgs::direction::left].second = true;
}
void sgs::Hero::stopGoLeft() {
  whereToMove[sgs::direction::left].second = false;
}
void sgs::Hero::beginGoRight() {
  whereToMove[sgs::direction::right].second = true;
}
void sgs::Hero::stopGoRight() {
  whereToMove[sgs::direction::right].second = false;
}

void sgs::Hero::beginShooting() {
  shootingCountdown = 0;
}

void sgs::Hero::stopShooting() {
  shootingCountdown = -1;
}

bool sgs::Hero::isFiring() {
  if (shootingCountdown > 0)
    --shootingCountdown;
  else {
    if (!shootingCountdown) {
      shootingCountdown = FIRING_COOLDOWN;
      return true;
    }
  }
  return false;
}

bool sgs::Hero::damageBullet(sf::Vector2f& bull) {
  if (bull == pos)
  {
    return true;
  }
  return false;
}

void sgs::Hero::update() {
  speed = {};

  if (whereToMove[sgs::direction::forward].second)
    speed.y -= 1;
  if (whereToMove[sgs::direction::right].second)
    speed.x += 1;
  if (whereToMove[sgs::direction::back].second)
    speed.y += 1;
  if (whereToMove[sgs::direction::left].second)
    speed.x -= 1;

  float lengthSpeed = static_cast< float >(sqrt(pow(speed.x, 2) + pow(speed.y, 2)));

  if (lengthSpeed) {
    speed /= lengthSpeed;
    speed *= sgs::SPEED_HERO;

    float angle = facingAngle / 180 * sgs::PI;

    sf::Vector2f temp = {
      speed.x * sin(angle) + speed.y * -cos(angle),
      speed.x * cos(angle) + speed.y * sin(angle),
    };

    speed = temp;

    pos += speed;
  }

  triangle.setPosition(pos - *screenPos);
}

const sf::Drawable& sgs::Hero::getSprite() {
  return triangle;
}
