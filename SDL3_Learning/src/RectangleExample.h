#pragma once
#include <SDL3/SDL.h>

class RectangleExample
{
private:
	SDL_FRect rectangle;
public:
	RectangleExample();
	RectangleExample(const float& x, const float& y, const float& side);
	RectangleExample(const float& x, const float& y, const float& w, const float& h);
	RectangleExample(const SDL_FRect& rect);
	bool SetPosition(const float& x, const float& y);
	bool UpdatePosition(const float& x, const float& y);
	bool SetScale(const float& w, const float& h);
	bool UpdateScale(const float& w, const float& h);
	bool Render(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};
