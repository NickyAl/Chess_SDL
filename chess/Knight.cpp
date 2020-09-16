#include "Knight.h"
#include <SDL_image.h>
#include <iostream>
#include <string>

Knight::Knight()
{
	_w = 90;
	_h = 90;
	_x = 0;
	_y = 0;
	_r = 180;
	_g = 180;
	_b = 10;
	_a = 200;
	_texture = LoadTexture("Resources/WhiteKnight.png");
	_marked = false;
	_team = 'W';
}

Knight::Knight(int w, int h, int x, int y, int r, int g, int b, int a, bool marked, char team)
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

Knight::Knight(int w, int h, int x, int y, const std::string& image_path, bool marked, char team)
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

Knight::~Knight()
{
	SDL_DestroyTexture(_texture);
}

void Knight::pollEvents(SDL_Event& event, char gridTeams[][9], size_t* rmvFig)
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
			x = (event.motion.x / 90) * 90;
			y = (event.motion.y / 90) * 90;

			if (gridTeams[y / 90][x / 90] != gridTeams[_y / 90][_x / 90])
			{
				if ((x == _x - 90 && y == _y + 180) ||
					(x == _x + 90 && y == _y + 180) ||
					(x == _x + 180 && y == _y + 90) ||
					(x == _x + 180 && y == _y - 90) ||
					(x == _x + 90 && y == _y - 180) ||
					(x == _x - 90 && y == _y - 180) ||
					(x == _x - 180 && y == _y - 90) ||
					(x == _x - 180 && y == _y + 90))
				{
					if (gridTeams[y / 90][x / 90] != '-')
					{
						rmvFig[1] = x / 90; //getting the coords of the figure we need to remove from the board
						rmvFig[0] = y / 90;
						rmvFig[2] = gridTeams[y / 90][x / 90];
					}

					gridTeams[_y / 90][_x / 90] = '-';
					_x = x;
					_y = y;
					gridTeams[_y / 90][_x / 90] = _team;
					_marked = false;
				}
			}
		}

		if (!(event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= _y && event.motion.y < (_y + _h)))
		{
			_marked = false;
		}

		break;

	default:
		break;
	}
}