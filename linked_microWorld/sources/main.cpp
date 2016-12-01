/**
* moz
*/

#include					<iostream>

#include					"Engine.hpp"

int							main() {
  std::cout << "Launching..." << std::endl;
  std::unique_ptr<Engine>	engine (new Engine());

  engine->init();

  engine->launch();

  return (0);
}
