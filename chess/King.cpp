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
	_team = 'W';
}

King::King(int w, int h, int x, int y, int r, int g, int b, int a, bool marked, char team)
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

King::King(int w, int h, int x, int y, const std::string& image_path, bool marked, char team)
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

King::~King()
{
	SDL_DestroyTexture(_texture);
}

void King::pollEvents(SDL_Event& event, char gridTeams[][9], char gridFigures[][9], size_t* rmvFig, char& turn)
{
	int x = _x, y = _y;
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
			if (gridTeams[y / 90][x / 90] == '-' && isUnguarded(gridTeams, gridFigures, x / 90, y / 90, _team))
			{
				gridTeams[_y / 90][_x / 90] = '-';
				gridFigures[_y / 90][_x / 90] = '-';
				_x = x;
				_y = y;
				gridTeams[_y / 90][_x / 90] = _team;
				gridFigures[_y / 90][_x / 90] = 'K';
				if (_team == 'W')
					turn = 'B';
				else
					turn = 'W';
			}
			else if (gridTeams[y / 90][x / 90] != gridTeams[_y / 90][_x / 90] && isUnguarded(gridTeams, gridFigures, x / 90, y / 90, _team))
			{
				rmvFig[1] = x / 90; //getting the coords of the figure we need to remove from the board
				rmvFig[0] = y / 90;
				rmvFig[2] = gridTeams[y / 90][x / 90];

				gridTeams[_y / 90][_x / 90] = '-';
				gridFigures[_y / 90][_x / 90] = '-';
				_x = x;
				_y = y;
				gridTeams[_y / 90][_x / 90] = _team;
				gridFigures[_y / 90][_x / 90] = 'K';
				if (_team == 'W')
					turn = 'B';
				else
					turn = 'W';
			}
			
		}

		break;

	default:
		break;
	}
}