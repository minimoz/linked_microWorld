/**
 * moz
 */

#ifndef					TILE_HPP__
# define				TILE_HPP__

# include				<iostream>

# include				<SFML/Graphics.hpp>

# include				"AEntity.hpp"
# include				"ResourceManager.hpp"

class					Tile : public AEntity {

public:
  Tile();
  Tile(const std::string &);
  ~Tile();

  int					init();
  void					setPosition(const std::pair<int, int> &);
};

#endif					/* TILE_HPP__ */
