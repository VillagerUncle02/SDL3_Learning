#include "RectangleExample.h"

RectangleExample::RectangleExample()
{
	rectangle = { 0, 0, 0, 0 };
}

RectangleExample::RectangleExample(const float& x, const float& y, const float& side)
{
	rectangle = { SDL_fabsf(x), SDL_fabsf(y), SDL_fabsf(side), SDL_fabsf(side) };
}

RectangleExample::RectangleExample(const float& x, const float& y, const float& w, const float& h)
{
	rectangle = { SDL_fabsf(x), SDL_fabsf(y), SDL_fabsf(w), SDL_fabsf(h) };
}

RectangleExample::RectangleExample(const SDL_FRect& rect)
	: rectangle(rect)
{
}

bool RectangleExample::SetPosition(const float& x, const float& y)
{
	rectangle.x = SDL_fabsf(x);
	rectangle.y = SDL_fabsf(y);
	return true;
}

bool RectangleExample::UpdatePosition(const float& x, const float& y)
{
	rectangle.x += x;
	rectangle.y += y;
	return true;
}

bool RectangleExample::SetScale(const float& w, const float& h)
{
	rectangle.w = w;
	rectangle.h = h;
	return true;
}

bool RectangleExample::UpdateScale(const float& w, const float& h)
{
	rectangle.w += SDL_fabsf(w);
	rectangle.h += SDL_fabsf(h);
	return true;
}

bool RectangleExample::Render(SDL_Renderer * renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderRect(renderer, &rectangle);
	return true;
}
