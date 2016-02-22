/**
 * moz
 */

#include				<iostream>

#include				"../headers/Engine.hpp"
#include				"../headers/Map.hpp"

int						main() {
  std::cout << "Launching..." << std::endl;

  Map					*map = new Map(50, 50);

  Engine				*engine = new Engine(map);

  if (!engine->init()) {
	  std::cout << "An error occured during the initialization." << std::endl;
	  //return (-1);
  }
  engine->launch();

  return (0);
}
