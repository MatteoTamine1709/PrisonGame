#pragma once
#include <utility>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

typedef std::pair<int, int> Pair;
typedef std::pair<double, std::pair<int, int>> pPair;
typedef std::vector<std::vector<int>> Arr2D;

struct cell {
	int parent_i, parent_j;
	double f, g, h;
};

class Map
{
public:
	int COL = 20;
	int ROW = 20;
	Arr2D *grid;

	Map();
	Map(int row, int col, Arr2D& map);
	static Arr2D convertImageToGrid(sf::Image image);

};

