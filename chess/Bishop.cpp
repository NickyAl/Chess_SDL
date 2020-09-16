#include "Bishop.h"
#include <SDL_image.h>
#include <iostream>
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
	_team = 'W';
}

Bishop::Bishop(int w, int h, int x, int y, int r, int g, int b, int a, bool marked, char team)
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
	_team = team;
}

Bishop::Bishop(int w, int h, int x, int y, const std::string& image_path, bool marked, char team)
{
	_w = w;
	_h = h;
	_x = x;
	_y = y;
	_marked = marked;
	_team = team;

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

void Bishop::pollEvents(SDL_Event& event, char grid[][9])
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
				
				bool doMove = false;
				int x1 = x, y1 = y;
				
				//checking if there is figure blocking the path to the next move
				if (x - y == _x - _y)
				{
					if (x < _x)
					{
						while (y1 != _y) //if one coord is the same then both are the same
						{
							doMove = (grid[y1 / 90][x1 / 90] == '-' );
							y1 += 90;
							x1 += 90;
							if (!doMove)
								break;
						}
					}
					else
					{
						while (y1 != _y)
						{
							doMove = (grid[y1 / 90][x1 / 90] == '-');
							y1 -= 90;
							x1 -= 90;
						
							if (!doMove)
								break;
						}
					}
				}
				if (x + y == _x + _y)
				{
					if (x > _x)
					{
						while (y1 != _y)
						{
							doMove = (grid[y1 / 90][x1 / 90] == '-');
							y1 += 90;
							x1 -= 90;

							if (!doMove)
								break;
						}
					}
					else
					{
						while (y1 != _y)
						{
							doMove = (grid[y1 / 90][x1 / 90] == '-');
							y1 -= 90;
							x1 += 90;

							if (!doMove)
								break;
						}
					}
				}
				std::cout << "DOMOVE = " << doMove << "\n";
				if (doMove)
				{
					grid[_y / 90][_x / 90] = '-';
					_x = x;
					_y = y;
					grid[_y / 90][_x / 90] = _team;
					x = 720;
					y = 720;
				}
			}
		}

		break;

	default:
		break;
		}
}
