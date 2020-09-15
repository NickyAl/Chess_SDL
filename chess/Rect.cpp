#include "Rect.h"
#include <SDL_image.h>
#include <iostream>

Rect::Rect()
{
	_w = 0;
	_h = 0;
	_x = 0;
	_y = 0;
	_r = 0;
	_g = 0;
	_b = 0;
	_a = 0;
}

Rect::Rect(int w, int h, int x, int y, int r, int g, int b, int a) :
	_w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a)
{
}

Rect::~Rect()
{
}

void Rect::draw() const
{
	SDL_Rect rect = { _x, _y, _w, _h };

	SDL_SetRenderDrawColor(Window::renderer, _r, _g, _b, _a);
	SDL_RenderFillRect(Window::renderer, &rect);

}

void Rect::pollEvents(SDL_Event& event)
{
	switch (event.type)
	{

	case SDL_MOUSEMOTION:
		if (event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= _y && event.motion.y < (_y + _h))
		{
			_r = 60;
			_g = 180;
			_b = 60;
		}
		else
		{
			_r = 100;
			_g = 140;
			_b = 100;
		}

	default:
		break;
	}
}
