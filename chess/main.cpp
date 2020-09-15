#include "Window.h"
#include "Rect.h"
#include "Background.h"
#include "Pawn.h"
#include <iostream>
#include "Bishop.h"

void pollEvents(bool grid[][8], Window& window, Rect* moves, Pawn* pawns, Bishop* bishops)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		window.pollEvents(event);
		for(size_t i = 0; i < 2; i++)
			bishops[i].pollEvents(event, grid);
		for(size_t i = 0; i < 32; i++)
			moves[i].pollEvents(event);
		for (size_t i = 0; i < 8; i++) //we know have 8 pawns in the team probably gonna have to change to 16 later
			pawns[i].pollEvents(event, grid);
	}
}

int main(int argc, char** argv)
{
	Window window("SDL_TESTING", 720, 720);
	Background board(720, 720, 0, 0, "Resources/board2.jpg");

	bool grid[8][8]; //starts with all free
	for (size_t i = 0; i < 8; i++)
	{
		if (i != 7 && i != 6)
		{
			for (size_t j = 0; j < 8; j++)
			{
				grid[i][j] = 1;
			}
		}
		else
		{
			for (size_t j = 0; j < 8; j++)
			{
				grid[i][j] = 0;
			}
		}
	}

	Bishop bishops[2];
	for (size_t i = 0; i < 2; i++)
	{
		bishops[i].setW(90);
		bishops[i].setH(90);
		bishops[i].setX(180 + (270 * i));
		bishops[i].setY(630);
	}

	Pawn pawns[8];
	for (size_t i = 0; i < 8; i++)
	{
		pawns[i].setW(90);
		pawns[i].setH(90);
		pawns[i].setX(90 * i);
		pawns[i].setY(540);
	}

	Rect posMoves[32];
	for (size_t i = 0; i < 32; i++)
	{
		posMoves[i].setW(60);
		posMoves[i].setH(60);
		posMoves[i].setR(100);
		posMoves[i].setG(140);
		posMoves[i].setB(100);
		posMoves[i].setA(150);
	}

	while (!window.isClosed())
	{
		pollEvents(grid ,window, posMoves, pawns, bishops);
		board.draw();

		for (size_t i = 0; i < 2; i++)
		{
			bishops[i].draw();

			if (bishops[i].getMarked())
			{
				for (size_t j = 0, k = 0; j < 32; j += 4, k++)
				{
					posMoves[j].setX(bishops[i].getX() - 75 - (90 * k));
					posMoves[j].setY(bishops[i].getY() - 75 - (90 * k));

					posMoves[j].draw();

					posMoves[j + 1].setX(bishops[i].getX() + 105 + (90 * k));
					posMoves[j + 1].setY(bishops[i].getY() + 105 + (90 * k));

					posMoves[j + 1].draw();

					posMoves[j + 2].setX(bishops[i].getX() + 105 + (90 * k));
					posMoves[j + 2].setY(bishops[i].getY() - 75 - (90 * k));

					posMoves[j + 2].draw();

					posMoves[j + 3].setX(bishops[i].getX() - 75 - (90 * k));
					posMoves[j + 3].setY(bishops[i].getY() + 105 + (90 * k));

					posMoves[j + 3].draw();
				}
			}
		}

		for (size_t i = 0; i < 8; i++)
		{
			pawns[i].draw();

			if (pawns[i].getMarked())
			{
				for (size_t j = 0; j < 2; j++)
				{
					posMoves[j].setX(pawns[i].getX() + 15);
					posMoves[j].setY(pawns[i].getY() - 75 - (90 * j));

					posMoves[j].draw();

					if (pawns[i].getY() != 540)
						break;
				}
			}
		}

		window.clear();
	}

	return 0;
}