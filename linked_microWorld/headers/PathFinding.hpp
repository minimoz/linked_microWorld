/**
* moz
*/

#ifndef											PATH_FINDING_HPP__
# define										PATH_FINDING_HPP__

# include										<memory>
# include										<vector>
# include										<algorithm>

class											Map;

struct											_SPoint {
	std::shared_ptr<_SPoint>					parent = nullptr;
	int											x = 0;
	int											y = 0;
	int											f = 0;
	int											g = 0;
	int											h = 0;
	bool										closed = false;
	bool										opened = false;

	_SPoint(int x, int y) : x(x), y(y) {}
};

class											PathFinding {
private:
	std::vector<std::shared_ptr<_SPoint> >		_openList;
	std::vector<std::shared_ptr<_SPoint> >		_closeList;

	std::unique_ptr<Map>						&_map;

public:
	PathFinding(std::unique_ptr<Map> &);
	~PathFinding();

	std::shared_ptr<_SPoint>					getPoint(int x, int y);
	int											getGScore(const std::shared_ptr<_SPoint> &, const std::shared_ptr<_SPoint> &);
	int											getHScore(const std::shared_ptr<_SPoint> &, const std::shared_ptr<_SPoint> &);
	void										computeScores(std::shared_ptr<_SPoint> &, const std::shared_ptr<_SPoint> &);
	void										addAdjacentTile(const std::shared_ptr<_SPoint> &, std::shared_ptr<_SPoint> &, const std::shared_ptr<_SPoint> &);
	std::vector<std::pair<int, int> >			aStar(int, int, int, int);

/*private:
	const std::shared_ptr<_SPoint>				getPoint(int, int);*/

};

#endif											/* PATH_FINDING_HPP__ */
