/**
 * moz
 */

#ifndef									MAP_HPP__
# define								MAP_HPP__

# include								<iostream>
# include								<vector>
# include								<memory>

# include								<SFML/Graphics.hpp>

# include								"Tile.hpp"
# include								"Person.hpp"

# define								WIDTH_DEFAULT_	50
# define								HEIGHT_DEFAULT_	50

class									Map {

private:
  int									_width;
  int									_height;
  std::vector<std::shared_ptr<Tile> >	_map;
  std::vector<std::shared_ptr<Person> >	_persons;

public:
  Map();
  Map(const int &, const int &);
  ~Map();

  const int&							getWidth();
  const int&							getHeight();

  int									init();
  void									update();
  void									draw(sf::RenderWindow *);
  int									addPerson();
  bool									isAnyPersonOnTile(const int &, const int &);

private:
  const std::pair<int, int>&			convertSmpDimToDblDim(const int &);

};

#endif									/* MAP_HPP__ */
