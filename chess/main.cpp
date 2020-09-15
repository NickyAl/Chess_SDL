#include "Window.h"
#include "Rect.h"
#include "Background.h"
#include "Pawn.h"
#include <iostream>
#include "Bishop.h"

//OPM - of possible moves
void pollEvents(Window& window, Rect*& moves, size_t sizeOPM, Pawn*& pawns, size_t sizeOfPawns, Bishop*& bishops, size_t sozeOfBishops)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		window.pollEvents(event);
		for(size_t i = 0; i < sozeOfBishops; i++)
			bishops[i].pollEvents(event);
		for(size_t i = 0; i < sizeOPM; i++)
			moves[i].pollEvents(event);
		for (size_t i = 0; i < sizeOfPawns; i++) //we know have 8 pawns in the team probably gonna have to change to 16 later
			pawns[i].pollEvents(event);
	}
}

int main(int argc, char** argv)
{
	Window window("SDL_TESTING", 720, 720);
	Background board(720, 720, 0, 0, "Resources/board2.jpg");
	Bishop bishop(90, 90, 630, 450, "Resources/WhiteBishop.png", false);

	size_t nob = 2; //number of bishops
	Bishop* bishops = new Bishop [nob];
	for (size_t i = 0; i < nob; i++)
	{
		bishops[i].setW(90);
		bishops[i].setH(90);
		bishops[i].setX(180 + (270 * i));
		bishops[i].setY(630);
	}

	size_t nopwns = 8; //number of pawns
	Pawn *pawns = new Pawn [8];
	for (size_t i = 0; i < nopwns; i++)
	{
		pawns[i].setW(90);
		pawns[i].setH(90);
		pawns[i].setX(90 * i);
		pawns[i].setY(540);
	}

	size_t nopm = 32; //number of possible moves
	Rect* posMoves = new Rect[nopm];
	for (size_t i = 0; i < nopm; i++)
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
		pollEvents(window, posMoves, nopm, pawns, nopwns, bishops, nob);
		board.draw();

		for (size_t i = 0; i < nob; i++)
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

		for (size_t i = 0; i < nopwns; i++)
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

	delete[] pawns;
	//delete [] posMoves;
	return 0;
}