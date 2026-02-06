#pragma once
#include <vector>
#include <SDL3/SDL.h>


//Two array,points array and the speed of point array, is required.

class PointsExample
{
private:
	std::vector<SDL_FPoint> points;
	std::vector<float> point_speeds;
	int point_size;
	int x_border;
	int y_border;
	float point_min_speed;
	float point_max_speed;
public:
	PointsExample(const int& pointSize, const int& xBorder, const int& yBorder, const float& pointMinSpeed = 20, const float& pointMaxpeed = 100);
	bool UpdatePoints(const float& deltaTime);
	bool Render(SDL_Renderer* renderer);
};