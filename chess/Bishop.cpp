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

void Bishop::pollEvents(SDL_Event& event, char gridTeams[][9], char gridFigures[][9], size_t* rmvFig, char& turn)
{
	int x = 720, y = 720;

	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:

		if (event.motion.x >= _x && event.motion.x < (_x + _w) && event.motion.y >= _y && event.motion.y < (_y + _h))
		{
			if(turn == _team)
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
			if (x != 720 && y != 720)
			{
				
				bool doMove = false;
				int x1 = _x, y1 = _y;
				
				//checking if there is figure blocking the path to the next move
				if (x - y == _x - _y)
				{
					if (x < _x)
					{
						while (y1 != y) //if one coord is the same then both are the same
						{
							y1 -= 90;
							x1 -= 90;
							doMove = (gridTeams[y1 / 90][x1 / 90] == '-' );

							if (!doMove && gridTeams[y1 / 90][x1 / 90] != gridTeams[_y / 90][_x / 90])
							{
								doMove = true;
								break;
							}

							if (!doMove)
								break;
						}
					}
					else
					{
						while (y1 != y)
						{
							y1 += 90;
							x1 += 90;
							doMove = (gridTeams[y1 / 90][x1 / 90] == '-');

							if (!doMove && gridTeams[y1 / 90][x1 / 90] != gridTeams[_y / 90][_x / 90])
							{
								doMove = true;
								break;
							}
						
							if (!doMove)
								break;
						}
					}
				}
				if (x + y == _x + _y)
				{
					if (x > _x)
					{
						while (y1 != y)
						{
							y1 -= 90;
							x1 += 90;
							doMove = (gridTeams[y1 / 90][x1 / 90] == '-');

							if (!doMove && gridTeams[y1 / 90][x1 / 90] != gridTeams[_y / 90][_x / 90])
							{
								doMove = true;
								break;
							}

							if (!doMove)
								break;
						}
					}
					else
					{
						while (y1 != y)
						{
							y1 += 90;
							x1 -= 90;
							doMove = (gridTeams[y1 / 90][x1 / 90] == '-');

							if (!doMove && gridTeams[y1 / 90][x1 / 90] != gridTeams[_y / 90][_x / 90])
							{
								doMove = true;
								break;
							}

							if (!doMove)
								break;
						}
					}
				}
				if (doMove)
				{
					if (gridTeams[y / 90][x / 90] != gridTeams[_y / 90][_x / 90])
					{
						if (x == x1 && y == y1)
						{
							rmvFig[1] = x / 90; //getting the coords of the figure we need to remove from the board
							rmvFig[0] = y / 90;
							rmvFig[2] = gridTeams[y / 90][x / 90];

							gridTeams[_y / 90][_x / 90] = '-';
							gridFigures[_y / 90][_x / 90] = '-';
							_x = x;
							_y = y;
							gridTeams[_y / 90][_x / 90] = _team;
							gridFigures[_y / 90][_x / 90] = 'b';
							x = 720;
							y = 720;
							if (_team == 'W')
								turn = 'B';
							else
								turn = 'W';
						}
					}
					else if (gridTeams[y1 / 90][x1 / 90] == '-')
					{
						gridTeams[_y / 90][_x / 90] = '-';
						gridFigures[_y / 90][_x / 90] = '-';
						_x = x;
						_y = y;
						gridTeams[_y / 90][_x / 90] = _team;
						gridFigures[_y / 90][_x / 90] = 'b';
						x = 720;
						y = 720;
						if (_team == 'W')
							turn = 'B';
						else
							turn = 'W';
					}
				}
			}
		}

		break;

	default:
		break;
		}
}
