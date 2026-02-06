#include <SDL3/SDL.h>

#include "marcoLib.h"
#include "pointsExample.h"


PointsExample::PointsExample(const int& pointSize, const int& xBorder, const int& yBorder, const float& pointMinSpeed, const float& pointMaxSpeed)
	: point_size(pointSize), x_border(xBorder), y_border(yBorder), point_min_speed(pointMinSpeed), point_max_speed(pointMaxSpeed)
{
	for (int i = 0; i < pointSize; i++)
	{
		points.push_back({SDL_randf() * x_border, SDL_randf() * y_border});
		point_speeds.push_back(point_min_speed + SDL_randf() * (point_max_speed - point_min_speed));
	}
}

bool PointsExample::UpdatePoints(const float& deltaTime)
{
	for (int i = 0; i < point_size; i++)
	{
		points[i].x += point_speeds[i] * deltaTime;
		points[i].y += point_speeds[i] * deltaTime;
		if (points[i].x >= x_border || points[i].y >= y_border)
		{
			if (SDL_rand(2))
			{
				points[i].x = SDL_randf() * x_border;
				points[i].y = 0;
			}
			else
			{
				points[i].x = 0;
				points[i].y = SDL_randf() * y_border;
			}
			point_speeds[i] = point_min_speed + SDL_randf() * (point_max_speed - point_min_speed);
		}
	}
	return true;
}

bool PointsExample::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, (Uint8)255, (Uint8)255, (Uint8)255, SDL_ALPHA_OPAQUE);
	SDL_RenderPoints(renderer, points.data(), static_cast<int>(points.size()));
	return true;
}
