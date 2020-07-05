#pragma once
#include <vector>
#include <stack>
#include <set>
#include "Map.h"

class AI
{
private:
	std::vector<Pair> m_path;
	Map* m_map;
	std::stack<Pair> Path;
public:
	Pair pos;
	Pair dest;
	void getPath(void);
	AI(Map& map);
	AI(void);
	bool checkCell(int i, int j, int pi, int pj, std::vector<std::vector<cell>>& cellDetails, std::set<pPair>& openList,
		std::vector<std::vector<bool>>& closedList, Arr2D& grid, float val);

private:
	bool isValid(int row, int col);
	bool isUnBlocked(Arr2D grid, int row, int col);
	bool isDestination(int row, int col, Pair dest);
	double calculateHValue(int row, int col, Pair dest);
	void tracePath(std::vector<std::vector<cell>> cellDetails, Pair dest);
	void aStarSearch(Arr2D& grid, Pair& src, Pair& dest);

};

