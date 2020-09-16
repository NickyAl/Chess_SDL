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
	_team = 'W';
}

Rook::Rook(int w, int h, int x, int y, int r, int g, int b, int a, bool marked, char team)
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

Rook::Rook(int w, int h, int x, int y, const std::string& image_path, bool marked, char team)
{
	_w = w;
	_h = h;
	_x = x;
	_y = y;
	_team = team;
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

void Rook::pollEvents(SDL_Event& event, char gridTeams[][9], char gridFigures[][9], size_t* rmvFig)
{
	int x = 720, y = 720;
	char otherTeam = 'B';
	if (_team == 'B')
		otherTeam == 'W';

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
			int x1 = _x, y1 = _y;

			if (x != 720 && y != 720)
			{
				if (x == _x)
				{
					if (y < _y)
					{
						while (y1 != y)
						{
							y1 -= 90;
							doMove = (gridTeams[y1 / 90][x1 / 90] == '-');
							
							if (!doMove && gridTeams[y1 / 90][x1 / 90] == otherTeam)
							{
								doMove = true;
								break;
							}
							
							if (!doMove)
							{
								break;
							}
						}
					}
					if (y > _y)
					{
						while (y1 != y)
						{
							y1 += 90;
							doMove = (gridTeams[y1 / 90][x1 / 90] == '-');

							if (!doMove && gridTeams[y1 / 90][x1 / 90] == otherTeam)
							{
								doMove = true;
								break;
							}
							if (!doMove)
							{
								break;
							}
						}
					}
				}
				if (y == _y)
				{
					if (x < _x)
					{
						while (x1 != x)
						{
							x1 -= 90;
							doMove = (gridTeams[y1 / 90][x1 / 90] == '-');

							if (!doMove && gridTeams[y1 / 90][x1 / 90] == otherTeam)
							{
								doMove = true;
								break;
							}
							if (!doMove)
							{
								break;
							}
						}
					}
					if (x > _x)
					{
						while (x1 != x)
						{
							x1 += 90;
							doMove = (gridTeams[y1 / 90][x1 / 90] == '-');
							
							if (!doMove && gridTeams[y1 / 90][x1 / 90] == otherTeam)
							{
								doMove = true;
								break;
							}
							if (!doMove)
							{
								break;
							}
						}
					}
				}
				
				if (doMove)
				{
					if (gridTeams[y1 / 90][x1 / 90] == otherTeam)
					{
						std::cout << "INSIDE OF FIRST IF x1 = " << x1 << " y1 = " << y1 << "\n";
						if (x == x1 && y == y1)
						{
							rmvFig[1] = x / 90; //getting the coords of the figure we need to remove from the board
							rmvFig[0] = y / 90;
							rmvFig[2] = otherTeam;

							gridTeams[_y / 90][_x / 90] = '-';
							gridFigures[_y / 90][_x / 90] = '-';
							_x = x;
							_y = y;
							gridTeams[_y / 90][_x / 90] = _team;
							gridFigures[_y / 90][_x / 90] = 'r';
							x = 720;
							y = 720;
						}
					}
					else
					{
						std::cout << "ELSE\n";
						gridTeams[_y / 90][_x / 90] = '-';
						gridFigures[_y / 90][_x / 90] = '-';
						_x = x;
						_y = y;
						gridTeams[_y / 90][_x / 90] = _team;
						gridFigures[_y / 90][_x / 90] = 'r';
						x = 720;
						y = 720;
					}
					
				}	
			}
		}

		break;

	default:
		break;
	}
}
