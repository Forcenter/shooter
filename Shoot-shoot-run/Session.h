#ifndef SESSION_H
#define SESSION_H

#include <map>

#include "SFML/Graphics.hpp"
#include "constants.h"
#include "Hero.h"
#include "Swordsman.h"
#include "SwordAttack.h"
#include "bullet.h"
#include "Block.h"

class Session {
private:
  sf::RenderWindow window;
  sf::Vector2f screenPos;
  sf::Vector2f screenPosFluid;

  std::pair< sf::Keyboard::Key, sgs::keyStatus > keyInputs[sgs::SUPPORTED_KEY_NUMBER];

  sgs::Hero hero;

  std::vector< Bullet > bullets;
  std::vector< Block > blocks;

  std::vector< std::unique_ptr< Enemy > > enemies;
  std::vector< std::unique_ptr< SwordAttack > > attacks;

  std::map< std::pair< sf::Keyboard::Key, sgs::keyStatus >, void (sgs::Hero::*)() > keyToFunction;

  size_t inputsPresent;
  void processInputs();
  void processEvents();

  sf::Vector2f createScreenStep();

  void checkIfPlayerIsShooting();

public:
  Session();

  bool isActive();

  void update();

  void draw();
};

#endif