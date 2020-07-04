#include <cmath>

float dist(float x1, float y1, float x2, float y2)
{
	float xd = (x1 - x2) * (x1 - x2);
	float yd = (y1 - y2) * (y1 - y2);

	return (sqrt((xd + yd)));
}