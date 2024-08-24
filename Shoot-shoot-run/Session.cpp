#include "Session.h"
#include <memory>

void Session::processEvents() {
  for (auto& it : enemies) {
    GameEvent e = it->getNewEvent();
    if (e.type == GameEvent::EventType::SwordAttack) {
      attacks.push_back(std::make_unique< SwordAttack >(it->getPosition(), it->getAngle(), &screenPosFluid));
    }
  }
}

void Session::processInputs() {
  inputsPresent = 0;
  sf::Event e;
  while (window.pollEvent(e)) {
    switch (e.type)
    {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        if (inputsPresent == sgs::SUPPORTED_KEY_NUMBER)
          throw;
        
        keyInputs[inputsPresent] = std::pair< sf::Keyboard::Key, sgs::keyStatus >(e.key.code, sgs::keyStatus::pressed);
        ++inputsPresent;
        break;
      case sf::Event::KeyReleased:
        if (inputsPresent == sgs::SUPPORTED_KEY_NUMBER)
          throw;
        
        keyInputs[inputsPresent] = std::pair< sf::Keyboard::Key, sgs::keyStatus >(e.key.code, sgs::keyStatus::released);
        ++inputsPresent;
        break;
      case sf::Event::MouseButtonPressed:
        if (e.mouseButton.button == sf::Mouse::Button::Left)
          hero.beginShooting();
        break;
      case sf::Event::MouseButtonReleased:
        if (e.mouseButton.button == sf::Mouse::Button::Left)
          hero.stopShooting();
        break;
    }
  }
}

Session::Session() :
  window(sf::VideoMode(sgs::WINDOW_WIDTH, sgs::WINDOW_HEIGHT), "Kto prochital tot Egorchik"),
  inputsPresent(0),
  hero(),
  screenPos(),
  screenPosFluid()
{
  window.setFramerateLimit(60);
  hero.setPos(300, 300);
  hero.setScreen(&screenPosFluid);
  blocks.push_back(Block({ 100, 100 }, { 50, 50 }, &screenPosFluid));

  enemies.push_back(std::make_unique< Swordsman >(sf::Vector2f{-100.f, -100.f}, &screenPosFluid));

  keyToFunction.insert({ { sf::Keyboard::Key::W, sgs::keyStatus::pressed }, &sgs::Hero::beginGoForward });
  keyToFunction.insert({ { sf::Keyboard::Key::W, sgs::keyStatus::released }, &sgs::Hero::stopGoForward });
  keyToFunction.insert({ { sf::Keyboard::Key::D, sgs::keyStatus::pressed }, &sgs::Hero::beginGoRight });
  keyToFunction.insert({ { sf::Keyboard::Key::D, sgs::keyStatus::released }, &sgs::Hero::stopGoRight });
  keyToFunction.insert({ { sf::Keyboard::Key::S, sgs::keyStatus::pressed }, &sgs::Hero::beginGoBack });
  keyToFunction.insert({ { sf::Keyboard::Key::S, sgs::keyStatus::released }, &sgs::Hero::stopGoBack });
  keyToFunction.insert({ { sf::Keyboard::Key::A, sgs::keyStatus::pressed }, &sgs::Hero::beginGoLeft });
  keyToFunction.insert({ { sf::Keyboard::Key::A, sgs::keyStatus::released }, &sgs::Hero::stopGoLeft });
}

sf::Vector2f Session::createScreenStep() {
  sf::Vector2f temp = (screenPos - screenPosFluid) / sgs::SCREEN_SPEED;
  if (sqrt(temp.x * temp.x + temp.y * temp.y) < sgs::MIN_SCREEN_STEP) {
    return screenPos - screenPosFluid;
  }
  return temp;
}

bool Session::isActive() {
  return window.isOpen();
}

void Session::update() {
  {
    std::vector< std::unique_ptr< SwordAttack > >::const_iterator it = attacks.begin();
    int index = 0;
    while (it != attacks.end()) {
      if (!it->get()->isAlive()) {
        attacks.erase(it);
        it = attacks.begin() + index;
      }
      else {
        ++index;
        ++it;
      }
    }
  }

  processInputs();
  checkIfPlayerIsShooting();
  for (size_t i = 0; i < inputsPresent; ++i) {
    auto it = keyToFunction.find(keyInputs[i]);
    if (it != keyToFunction.end())
      (hero.*it->second)();
  }

  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  hero.lookAt(mousePos);

  hero.update();
  for (auto& it: enemies)
    it->update(hero.getPosition());
  processEvents();
  for (auto& it: attacks)
    it->update();

  for (auto& x: bullets)
    x.update();
  for (auto& x: blocks)
    x.update();

  sf::Vector2f heroPos = hero.getPosition();

  screenPos = (heroPos - sf::Vector2f(sgs::WINDOW_WIDTH, sgs::WINDOW_HEIGHT) + sf::Vector2f(mousePos) + screenPos) / 2.f;
  sf::Vector2f dist = screenPos + sf::Vector2f{ sgs::WINDOW_WIDTH, sgs::WINDOW_HEIGHT } / 2.f - heroPos;
  float length = sqrt(dist.x * dist.x + dist.y * dist.y);
  if (length > sgs::MAX_DISTANCE_TO_CAM) {
    dist *= sgs::MAX_DISTANCE_TO_CAM / length;
    screenPos = heroPos + dist - sf::Vector2f{ sgs::WINDOW_WIDTH, sgs::WINDOW_HEIGHT } / 2.f;
  }
  screenPosFluid += createScreenStep();
}

void Session::draw() {
  window.clear(sf::Color(200, 200, 200));
  window.draw(hero.getSprite());
  for (auto& x: bullets)
    window.draw(x.getSprite());
  for (auto& x: blocks)
    window.draw(x.getSprite());
  for (auto& x: enemies)
    window.draw(x->getSprite());
  for (auto& x: attacks)
    window.draw(x->getSprite());
  window.display();
}

void Session::checkIfPlayerIsShooting() {
  if (hero.isFiring())
    bullets.push_back(Bullet(hero.getPosition(), hero.getFacingAngle(), &screenPosFluid));
}
