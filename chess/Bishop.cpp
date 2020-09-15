#include "Bishop.h"
#include <SDL_image.h>
#include <iostream>
#include "Rect.h"
#include <string>

Bishop::Bishop()
{
	_w = 90;
	_h = 90;
	_x = 630;
	_y = 450;
	_r = 180;
	_g = 10;
	_b = 180;
	_a = 200;
	_texture = LoadTexture("Resources/WhiteBishop.png");
	_marked = false;
}

Bishop::Bishop(int w, int h, int x, int y, int r, int g, int b, int a, bool marked)
{
	_w = w;
	_h = h;
	_x = x;
	_y = y;
	_r = r;
	_g = g;
	_b = b;
	_a = a;
	_marked = marked;
}

Bishop::Bishop(int w, int h, int x, int y, const std::string& image_path, bool marked)
{
	_w = w;
	_h = h;
	_x = x;
	_y = y;

	_marked = marked;

	auto surface = IMG_Load(image_path.c_str()); //c_str converts it to a construct pointer
	if (!surface)
	{
		std::cerr << "Failed to create surface\n";
	}

	_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!_texture)
	{
		std::cerr << "Failed to create texture\n";
	}

	SDL_FreeSurface(surface);
}

Bishop::~Bishop()
{
	SDL_DestroyTexture(_texture);
}

void Bishop::pollEvents(SDL_Event& event, bool grid[][8])
{
	int x = 10000, y = 10000;
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:

		if (event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= _y && event.motion.y < (_y + _h))
		{
			_marked = true;
		}

		if (_marked)
		{
			if ((((event.motion.x / 90) * 90) - ((event.motion.y / 90) * 90) == _x - _y) || ((event.motion.x / 90) * 90 + ((event.motion.y / 90) * 90) == _x + _y))
			{
				x = (event.motion.x / 90) * 90;
				y = (event.motion.y / 90) * 90;
			}
		}

		if (!(event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= _y && event.motion.y < (_y + _h)))
		{
			_marked = false;
			if (x != 10000 && y != 10000)
			{
				if (grid[y / 90][x / 90] == true)
				{
					grid[_y / 90][_x / 90] = true;
					_x = x;
					_y = y;
					grid[_y / 90][_x / 90] = false;
					x = 10000;
					y = 10000;
				}
			}
		}

		break;

	case SDL_MOUSEBUTTONUP:
		//std::cout << "You relsead you mouse button\n";
		break;

	default:
		break;
		}
}
