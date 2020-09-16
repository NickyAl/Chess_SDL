#include "Pawn.h"
#include <SDL_image.h>
#include <iostream>
#include <string>

Pawn::Pawn()
{
	_w = 90;
	_h = 90;
	_x = 0;
	_y = 0;
	_r = 180;
	_g = 10;
	_b = 180;
	_a = 200;
	_texture = LoadTexture("Resources/WhitePawn.png");
	_marked = false;
	_team = 'W';
}

Pawn::Pawn(int w, int h, int x, int y, int r, int g, int b, int a, bool marked, char team)
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

Pawn::Pawn(int w, int h, int x, int y, const std::string& image_path, bool marked, char team)
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

Pawn::~Pawn()
{
	SDL_DestroyTexture(_texture);
}

void Pawn::pollEvents(SDL_Event& event, char grid[][9])
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:


		if (event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= _y && event.motion.y < (_y + _h))
		{
			_marked = true;
		}
		
		if (_team == 'W')
		{
			if ((_marked) && (event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= (_y - 90) && event.motion.y < (_y - 90 + _h)))
			{
				if (grid[(_y - 90) / 90][_x / 90] == '-')
				{
					grid[_y / 90][_x / 90] = '-';
					_y -= 90;
					grid[_y / 90][_x / 90] = _team;
					_marked = false;
				}
			}
			if ((_marked) && ((_y == 540) && (event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= (_y - 180) && event.motion.y < (_y - 180 + _h))))
			{
				if (grid[(_y - 180) / 90][_x / 90] == '-')
				{
					if (grid[(_y - 90) / 90][_x / 90] == '-') //checking if there is figure blocking the path to the move
					{
						grid[_y / 90][_x / 90] = '-';
						_y -= 180;
						grid[_y / 90][_x / 90] = _team;
						_marked = false;
					}
				}
			}
		}
		else
		{
			if ((_marked) && (event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= (_y + 90) && event.motion.y < (_y + 90 + _h)))
			{
				if (grid[(_y + 90) / 90][_x / 90] == '-')
				{
					grid[_y / 90][_x / 90] = '-';
					_y += 90;
					grid[_y / 90][_x / 90] = _team;
					_marked = false;
				}
			}
			if ((_marked) && ((_y == 90) && (event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= (_y + 180) && event.motion.y < (_y + 180 + _h))))
			{
				if (grid[(_y + 180) / 90][_x / 90] == '-')
				{
					if (grid[(_y + 90) / 90][_x / 90] == '-') //checking if there is figure blocking the path to the move
					{
						grid[_y / 90][_x / 90] = '-';
						_y += 180;
						grid[_y / 90][_x / 90] = _team;
						_marked = false;
					}
				}
			}
		}

		if (!(event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= _y && event.motion.y < (_y + _h)))
		{
			_marked = false;
		}
		
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_x: //DEBUG FEATURE
			for (size_t i = 0; i < 8; i++)
			{
				for (size_t j = 0; j < 8; j++)
				{
					std::cout << grid[i][j] << "  ";
				}
				std::cout << "\n";
			}
			std::cout << "\n\n";
			break;

		default:
			break;
		}
	default:
		break;
	}
}