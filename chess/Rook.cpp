#include "Rook.h"
#include <SDL_image.h>
#include <iostream>
#include <string>

Rook::Rook()
{
	_w = 90;
	_h = 90;
	_x = 630;
	_y = 450;
	_r = 10;
	_g = 180;
	_b = 180;
	_a = 200;
	_texture = LoadTexture("Resources/WhiteRook.png");
	_marked = false;
}

Rook::Rook(int w, int h, int x, int y, int r, int g, int b, int a, bool marked)
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

Rook::Rook(int w, int h, int x, int y, const std::string& image_path, bool marked)
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

Rook::~Rook()
{
	SDL_DestroyTexture(_texture);
}

void Rook::pollEvents(SDL_Event& event, char grid[][8])
{
	int x = 10000, y = 10000;
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:

		if (event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= _y && event.motion.y < (_y + _h))
		{
			x = (event.motion.x / 90) * 90;
			y = (event.motion.y / 90) * 90;

			_marked = true;
		}

		if (_marked)
		{
			if (((event.motion.x / 90) * 90) == _x)
			{
				y = (event.motion.y / 90) * 90;
				x = _x;
			}
			else if (((event.motion.y / 90) * 90) == _y)
			{
				x = (event.motion.x / 90) * 90;
				y = _y;
			}
		}

		if ((_marked) && (!(event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= _y && event.motion.y < (_y + _h))))
		{
			_marked = false;

			bool doMove = false;
			int x1 = x, y1 = y;

			if (x != 10000 && y != 10000)
			{
				if (x == _x)
				{
					if (y < _y)
					{
						while (y1 != _y)
						{
							doMove = (grid[y1 / 90][x1 / 90] == '-');
							y1 += 90;
							if (!doMove)
								break;
						}
					}
					if (y > _y)
					{
						while (y1 != _y)
						{
							doMove = (grid[y1 / 90][x1 / 90] == '-');
							y1 -= 90;

							if (!doMove)
								break;
						}
					}
				}
				if (y == _y)
				{
					if (x < _x)
					{
						while (x1 != _x)
						{
							doMove = (grid[y1 / 90][x1 / 90] == '-');
							x1 += 90;

							if (!doMove)
								break;
						}
					}
					if (x > _x)
					{
						while (x1 != _x)
						{
							doMove = (grid[y1 / 90][x1 / 90] == '-');
							x1 -= 90;

							if (!doMove)
								break;
						}
					}
				}
				
				if (doMove)
				{
					grid[_y / 90][_x / 90] = '-';
					_x = x;
					_y = y;
					grid[_y / 90][_x / 90] = 'W';
					x = 10000;
					y = 10000;
				}	
			}
		}

		break;

	default:
		break;
	}
}