/**
* moz
*/

#ifndef								AIV1_HPP__
# define							AIV1_HPP__

# include							<iostream>
# include							<memory>

# include							<SFML/Graphics.hpp>

class								Tile;
class								Map;
class								PersonSpirit;

class								AIv1 {

private:
	std::unique_ptr<Map>			&_map;

public:
	AIv1(std::unique_ptr<Map> &);
	~AIv1();

	std::pair<int, int>				getTargetTile(const std::vector<std::shared_ptr<Tile> > &, const PersonSpirit &);
};

#endif								/* AIV1_HPP__ */
