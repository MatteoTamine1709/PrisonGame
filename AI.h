#pragma once
#include <vector>
#include <stack>
#include <set>
#include "Map.h"

class AI
{
protected:
	Map* m_map = nullptr;
	sf::Vector2f m_dir = { 0, 0 };
	float m_speed = 5;
	std::vector<std::vector<cell>> m_cellDetails;
	std::vector<std::vector<bool>> m_closedList;
public:
	sf::Vector2f Pos = { 100, 100 };
	sf::Vector2f Dest = Pos;
	std::stack<Pair> Path;
	AI(Map& map);
	AI(void);
	void getPath(void);
	void printPath(void);
	virtual void move(void);
	virtual void setMap(Map* map);
private:
	bool checkCell(int i, int j, int pi, int pj, std::vector<std::vector<cell>>& cellDetails, std::set<pPair>& openList,
		Arr2D& grid, float val, Pair& dest);
	bool isValid(int row, int col);
	bool isUnBlocked(Arr2D grid, int row, int col);
	bool isDestination(int row, int col, Pair dest);
	double calculateHValue(int row, int col, Pair dest);
	void aStarSearch(Arr2D& grid, sf::Vector2f& src, sf::Vector2f& dest);
	void tracePath(std::vector<std::vector<cell>> cellDetails, Pair dest);

};

