#include "King.h"
#include <SDL_image.h>
#include <iostream>
#include <string>

King::King()
{
	_w = 90;
	_h = 90;
	_x = 630;
	_y = 450;
	_r = 60;
	_g = 50;
	_b = 200;
	_a = 200;
	_texture = LoadTexture("Resources/WhiteRook.png");
	_marked = false;
}

King::King(int w, int h, int x, int y, int r, int g, int b, int a, bool marked)
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

King::King(int w, int h, int x, int y, const std::string& image_path, bool marked)
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

King::~King()
{
	SDL_DestroyTexture(_texture);
}

void King::pollEvents(SDL_Event& event, char grid[][9])
{
	int x = 720, y = 720;
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:

		if (event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= _y && event.motion.y < (_y + _h))
		{
			_marked = true;
		}

		if (_marked)
		{
			if (((event.motion.x / 90) * 90 - _x == 90 || (event.motion.x / 90) * 90 - _x == -90 || (event.motion.x / 90) * 90 - _x == 0) &&
				((event.motion.y / 90) * 90 - _y == 90 || (event.motion.y / 90) * 90 - _y == -90 || (event.motion.y / 90) * 90 - _y == 0))
			{
				x = (event.motion.x / 90) * 90;
				y = (event.motion.y / 90) * 90;
			}
		}

		if ((_marked) && (!(event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= _y && event.motion.y < (_y + _h))))
		{
			_marked = false;
			if (grid[y / 90][x / 90] == '-')
			{
				grid[_y / 90][_x / 90] = '-';
				_x = x;
				_y = y;
				x = 720;
				y = 720;
				grid[_y / 90][_x / 90] = 'W';
			}
		}

		break;

	default:
		break;
	}
}