#include "Window.h"
#include "Rect.h"
#include "Background.h"
#include "Pawn.h"
#include <iostream>
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"

void pollEvents(char grid[][8], Window& window, Rect* moves, Pawn* pawns, Bishop* bishops, Knight* knights, Rook* rooks)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		//poll events for the window
		window.pollEvents(event);
		
		//poll events for possible moves
		for (size_t i = 0; i < 32; i++)
			moves[i].pollEvents(event);

		//poll events for figures
		for(size_t i = 0; i < 2; i++)
			bishops[i].pollEvents(event, grid);
		for (size_t i = 0; i < 8; i++) //we know have 8 pawns in the team probably gonna have to change to 16 later
			pawns[i].pollEvents(event, grid);
		for (size_t i = 0; i < 2; i++)
			knights[i].pollEvents(event, grid);
		for (size_t i = 0; i < 2; i++)
			rooks[i].pollEvents(event, grid);
	}
}

int main(int argc, char** argv)
{
	Window window("SDL_TESTING", 720, 720);
	Background board(720, 720, 0, 0, "Resources/board2.jpg");

	char grid[8][8]; //starts with all free
	for (size_t i = 0; i < 8; i++)
	{
		if (i != 7 && i != 6)
		{
			for (size_t j = 0; j < 8; j++)
			{
				grid[i][j] = '-';
			}
		}
		else
		{
			for (size_t j = 0; j < 8; j++)
			{
				grid[i][j] = 'W';
			}
		}
	}

	Rook rooks[2];
	for (size_t i = 0; i < 2; i++)
	{
		rooks[i].setW(90);
		rooks[i].setH(90);
		rooks[i].setX(0 + (630 * i));
		rooks[i].setY(630);
	}

	Knight knights[2];
	for (size_t i = 0; i < 2; i++)
	{
		knights[i].setW(90);
		knights[i].setH(90);
		knights[i].setX(90 + (450 * i));
		knights[i].setY(630);
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
		posMoves[i].setW(50);
		posMoves[i].setH(50);
		posMoves[i].setR(100);
		posMoves[i].setG(140);
		posMoves[i].setB(100);
		posMoves[i].setA(150);
	}

	while (!window.isClosed())
	{
		pollEvents(grid ,window, posMoves, pawns, bishops, knights, rooks);
		board.draw();

		for (size_t i = 0; i < 2; i++)
		{
			rooks[i].draw();

			if (rooks[i].getMarked())
			{
				for (size_t j = 0, k = 0; j < 32; j += 4, k++)
				{
					posMoves[j].setX(rooks[i].getX() + 20);
					posMoves[j].setY(rooks[i].getY() - 70 - (90 * k));
					posMoves[j].draw();

					posMoves[j + 1].setX(rooks[i].getX() + 20);
					posMoves[j + 1].setY(rooks[i].getY() + 110 + (90 * k));
					posMoves[j + 1].draw();

					posMoves[j + 2].setX(rooks[i].getX() - 70 - (90 * k));
					posMoves[j + 2].setY(rooks[i].getY() + 20);
					posMoves[j + 2].draw();

					posMoves[j + 3].setX(rooks[i].getX() + 110 + (90 * k));
					posMoves[j + 3].setY(rooks[i].getY() + 20);
					posMoves[j + 3].draw();
				}
			}
		}

		for (size_t i = 0; i < 2; i++)
		{
			knights[i].draw();

			if (knights[i].getMarked())
			{
				posMoves[0].setX(knights[i].getX() - 90 + 20);
				posMoves[0].setY(knights[i].getY() + 180 + 20);
				posMoves[0].draw();

				posMoves[1].setX(knights[i].getX() + 90 + 20);
				posMoves[1].setY(knights[i].getY() + 180 + 20);
				posMoves[1].draw();

				posMoves[2].setX(knights[i].getX() + 180 + 20);
				posMoves[2].setY(knights[i].getY() + 90 + 20);
				posMoves[2].draw();

				posMoves[3].setX(knights[i].getX() + 180 + 20);
				posMoves[3].setY(knights[i].getY() - 90 + 20);
				posMoves[3].draw();

				posMoves[4].setX(knights[i].getX() + 90 + 20);
				posMoves[4].setY(knights[i].getY() - 180 + 20);
				posMoves[4].draw();

				posMoves[5].setX(knights[i].getX() - 90 + 20);
				posMoves[5].setY(knights[i].getY() - 180 + 20);
				posMoves[5].draw();

				posMoves[6].setX(knights[i].getX() - 180 + 20);
				posMoves[6].setY(knights[i].getY() - 90 + 20);
				posMoves[6].draw();

				posMoves[7].setX(knights[i].getX() - 180 + 20);
				posMoves[7].setY(knights[i].getY() + 90 + 20);
				posMoves[7].draw();
			}
		}

		for (size_t i = 0; i < 2; i++)
		{
			bishops[i].draw();

			if (bishops[i].getMarked())
			{
				for (size_t j = 0, k = 0; j < 32; j += 4, k++)
				{
					posMoves[j].setX(bishops[i].getX() - 70 - (90 * k));
					posMoves[j].setY(bishops[i].getY() - 70 - (90 * k));

					posMoves[j].draw();

					posMoves[j + 1].setX(bishops[i].getX() + 110 + (90 * k));
					posMoves[j + 1].setY(bishops[i].getY() + 110 + (90 * k));

					posMoves[j + 1].draw();

					posMoves[j + 2].setX(bishops[i].getX() + 110 + (90 * k));
					posMoves[j + 2].setY(bishops[i].getY() - 70 - (90 * k));

					posMoves[j + 2].draw();

					posMoves[j + 3].setX(bishops[i].getX() - 70 - (90 * k));
					posMoves[j + 3].setY(bishops[i].getY() + 110 + (90 * k));

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
					posMoves[j].setX(pawns[i].getX() + 20);
					posMoves[j].setY(pawns[i].getY() - 70 - (90 * j));

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