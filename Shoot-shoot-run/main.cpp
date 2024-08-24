#include <iostream>
#include "SFML/Graphics.hpp"
#include "constants.h"
#include "Session.h"
#include <string>

int main() {
  Session Session;

  while (Session.isActive()) {
    Session.update();
    Session.draw();
  }

  return 0;
}