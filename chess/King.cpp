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
				gridFigures[8][8] = 'K';
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
				gridFigures[8][8] = 'K';
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

bool King::checkmate(char gridTeams[][9], char gridFigures[][9])
{
	bool isCheckmate = true;
	bool allAreFriendly = true;
	char attackingFig = '-';
	size_t counter = 0;


	if (_x / 90 > 0)
	{
		if(gridTeams[(_y / 90)][(_x / 90) - 1] == '-')
			isCheckmate = isCheckmate && !isUnguarded(gridTeams, gridFigures, (_x/90) - 1,(_y / 90), _team);
	}
	if (_x / 90 < 7)
	{
		if (gridTeams[_y / 90][(_x / 90) + 1] == '-')
			isCheckmate = isCheckmate && !isUnguarded(gridTeams, gridFigures, (_x / 90) + 1, (_y/90), _team);
	}
	if (_y / 90 < 7)
	{
		if (gridTeams[(_y / 90) + 1][_x / 90] == '-')
			isCheckmate = isCheckmate && !isUnguarded(gridTeams, gridFigures, (_x / 90), (_y / 90) + 1, _team);
	}
	if (_y / 90 > 0)
	{
		if (gridTeams[(_y / 90) - 1][(_x / 90)] == '-')
			isCheckmate = isCheckmate && !isUnguarded(gridTeams, gridFigures, (_x / 90), (_y / 90) - 1, _team);
	}

	if (_x / 90 > 0 && _y / 90 > 0)
	{
		if (gridTeams[(_y / 90) - 1][(_x / 90) - 1] == '-')
			isCheckmate = isCheckmate && !isUnguarded(gridTeams, gridFigures, (_x / 90) - 1, (_y / 90) - 1, _team);
	}
	if (_x / 90 < 7 && _y / 90 < 7)
	{
		if (gridTeams[(_x / 90) + 1][_y / 90] == '-')
			isCheckmate = isCheckmate && !isUnguarded(gridTeams, gridFigures, (_x / 90) + 1, (_y / 90) + 1, _team);
	}
	if (_x / 90 > 0 && _y / 90 < 7)
	{
		if (gridTeams[(_y / 90) + 1][(_x / 90) - 1] == '-')
			isCheckmate = isCheckmate && !isUnguarded(gridTeams, gridFigures, (_x / 90) - 1, (_y / 90) + 1, _team);
	}
	if (_x / 90 < 7 && _y / 90 > 0)
	{
		if (gridTeams[(_y / 90) - 1][(_x / 90) + 1] == '-')
			isCheckmate = isCheckmate && !isUnguarded(gridTeams, gridFigures, (_x / 90) + 1, (_y / 90) - 1, _team);
	}
	//// 

	if (_x / 90 > 0)
	{
		allAreFriendly = allAreFriendly && (gridTeams[(_y / 90)][(_x / 90) - 1] == _team);
	}
	if (_x / 90 < 7)
	{
		allAreFriendly = allAreFriendly && (gridTeams[_y / 90][(_x / 90) + 1] == _team);
	}
	if (_y / 90 < 7)
	{
		allAreFriendly = allAreFriendly && (gridTeams[(_y / 90) + 1][_x / 90] == _team);
	}
	if (_y / 90 > 0)
	{
		allAreFriendly = allAreFriendly && (gridTeams[(_y / 90) - 1][(_x / 90)] == _team);
	}

	if (_x / 90 > 0 && _y / 90 > 0)
	{
		allAreFriendly = allAreFriendly && (gridTeams[(_y / 90) - 1][(_x / 90) - 1] == _team);
	}
	if (_x / 90 < 7 && _y / 90 < 7)
	{
		allAreFriendly = allAreFriendly && (gridTeams[(_x / 90) + 1][_y / 90] == _team);
	}
	if (_x / 90 > 0 && _y / 90 < 7)
	{
		allAreFriendly = allAreFriendly && (gridTeams[(_y / 90) + 1][(_x / 90) - 1] == _team);
	}
	if (_x / 90 < 7 && _y / 90 > 0)
	{
		allAreFriendly = allAreFriendly && (gridTeams[(_y / 90) - 1][(_x / 90) + 1] == _team);
	}
	
	isCheckmate = isCheckmate && !allAreFriendly;

	//checking what figure is attacking him
	//if they are more than one he cant move another fig to hide must move the king

	int i = _y / 90;
	int j = _x / 90;

	if (i > 0)
	{
		if (gridTeams[i - 1][j] != _team && gridTeams[i - 1][j] != '-' && gridFigures[i - 1][j] != 'k')
			attackingFig = gridFigures[i - 1][j];
	}
	if (i < 7)
	{
		if (gridTeams[i + 1][j] != _team && gridTeams[i + 1][j] != '-' && gridFigures[i + 1][j] != 'k')
			attackingFig = gridFigures[i + 1][j];

	}
	if (j > 0)
	{
		if (gridTeams[i][j - 1] != _team && gridTeams[i][j - 1] != '-' && gridFigures[i][j - 1] != 'k')
			attackingFig = gridFigures[i][j - 1];
	}
	if (j < 7)
	{
		if (gridTeams[i][j + 1] != _team && gridTeams[i][j + 1] != '-' && gridFigures[i][j + 1] != 'k')
			attackingFig = gridFigures[i][j + 1];
	}
	if (i > 0 && j > 0)
	{
		if (gridTeams[i - 1][j - 1] != _team && gridTeams[i - 1][j - 1] != '-' && gridFigures[i - 1][j - 1] != 'k')
			attackingFig = gridFigures[i - 1][j - 1];
	}
	if (i < 7 && j < 7)
	{
		if (gridTeams[i + 1][j + 1] != _team && gridTeams[i + 1][j + 1] != '-' && gridFigures[i + 1][j + 1] != 'k')
			attackingFig = gridFigures[i + 1][j + 1];
	}
	if (j > 0 && i < 7)
	{
		if (gridTeams[i + 1][j - 1] != _team && gridTeams[i + 1][j - 1] != '-' && gridFigures[i + 1][j - 1] != 'k')
			attackingFig = gridFigures[i + 1][j - 1];
	}
	if (j < 7 && i > 0)
	{
		if (gridTeams[i - 1][j + 1] != _team && gridTeams[i - 1][j + 1] != '-' && gridFigures[i - 1][j + 1] != 'k')
			attackingFig = gridFigures[i - 1][j + 1];
	}
	int k, l;
	k = j + 1;

	while (k - 1 < 7 && gridFigures[i][k] == '-')
	{
		k++;
		if (k - 1 < 7 && gridTeams[i][k] != _team && gridTeams[i][k + 1] != '-')
			if (gridFigures[i][k] == 'Q' || gridFigures[i][k] == 'b' || gridFigures[i][k] == 'r')
			{
				attackingFig = gridFigures[i][k];
				counter++;
			}
	}

	k = j - 1;

	while (k + 1 > 0 && gridFigures[i][k] == '-')
	{
		k--;
		if (k + 1 > 0 && gridFigures[i][k] != '-' && gridFigures[i][k] != _team)
			if (gridFigures[i][k] == 'Q' || gridFigures[i][k] == 'b' || gridFigures[i][k] == 'r')
			{
				attackingFig = gridFigures[i][k];
				counter++;
			}
	}
	k = i + 1;

	while (k - 1 < 7 && gridFigures[k][j] == '-')
	{
		k++;
		if (k - 1 < 7 && gridFigures[k][j] != '-' && gridFigures[k][j] != _team)
			if (gridFigures[k][j] == 'Q' || gridFigures[k][j] == 'b' || gridFigures[k][j] == 'r')
			{
				attackingFig = gridFigures[k][j];
				counter++;
			}
	}
	k = i - 1;

	while (k + 1 > 0 && gridFigures[k][j] == '-')
	{
		k--;
		if (k + 1 > 0 && gridFigures[k][j] != '-' && gridFigures[k][j] != _team)
			if (gridFigures[k][j] == 'Q' || gridFigures[k][j] == 'b' || gridFigures[k][j] == 'r')
			{
				attackingFig = gridFigures[k][j];
				counter++;
			}
	}

	k = i + 1;
	l = j + 1;

	while (k - 1 < 7 && l - 1 < 7 && gridFigures[k][l] == '-')
	{
		k++;
		l++;
		if (k - 1 < 7 && l - 1 < 7 && gridFigures[k][l] != '-' && gridFigures[k][l] != _team)
			if (gridFigures[k][l] == 'Q' || gridFigures[k][l] == 'b' || gridFigures[k][l] == 'r')
			{
				attackingFig = gridFigures[k][l];
				counter++;
			}
	}
	k = i + 1;
	l = j - 1;

	while (k - 1 < 7 && l + 1 > 0 && gridFigures[k][l] == '-')
	{
		k++;
		l--;
		if (k - 1 < 7 && l + 1 > 0 && gridFigures[k][l] != '-' && gridFigures[k][l] != _team)
			if (gridFigures[k][l] == 'Q' || gridFigures[k][l] == 'b' || gridFigures[k][l] == 'r')
			{
				attackingFig = gridFigures[k][l];
				counter++;
			}
	}
	k = i - 1;
	l = j + 1;

	while (k + 1 > 0 && l - 1 < 7 && gridFigures[k][l] == '-')
	{
		k--;
		l++;
		if (k + 1 > 0 && l + 1 < 7 && gridFigures[k][l] != '-' && gridFigures[k][l] != _team)
			if (gridFigures[k][l] == 'Q' || gridFigures[k][l] == 'b' || gridFigures[k][l] == 'r')
			{
				attackingFig = gridFigures[k][l];
				counter++;
			}
	}
	k = i - 1;
	l = j - 1;

	while (k + 1 > 0 && l + 1 > 0 && gridFigures[k][l] == '-')
	{
		k--;
		l--;
		if (l + 1 > 0 && k + 1 > 0 && gridFigures[k][l] != '-' && gridFigures[k][l] != _team)
			if (gridFigures[k][l] == 'Q' || gridFigures[k][l] == 'b' || gridFigures[k][l] == 'r')
			{
				attackingFig = gridFigures[k][l];
				counter++;
			}
	}

	std::cout << "attacking figure is  "<<attackingFig <<"\n";
	//Printing for debuging
	//if(isCheckmate)
	//	std::cout << "CHECKMATE\n";
	//else
	//	std::cout << "NOT checkmate\n";

	return isCheckmate;
}
