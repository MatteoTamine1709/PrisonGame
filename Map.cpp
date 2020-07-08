#include "Map.h"

Map::Map()
{
}

Map::Map(int row, int col, Arr2D& map)
	: ROW(row), COL(col), grid(&map)
{
}

Arr2D Map::convertImageToGrid(sf::Image image)
{
	Arr2D grid;
	grid.reserve(sizeof(std::vector<int>) * ((int)image.getSize().y / 10));
	for (unsigned int j = 0; j < image.getSize().y; j += 10) {
		std::vector<int> v;
		v.reserve(sizeof(int) * ((int)image.getSize().x / 10));
		for (unsigned int i = 0; i < image.getSize().x; i += 10)
			if (image.getPixel(i, j).r != 0 || image.getPixel(i, j).g != 0 ||
				image.getPixel(i, j).b != 0)
				v.push_back(0);
			else
				v.push_back(1);
		grid.push_back(v);
	}
	return (grid);
}
