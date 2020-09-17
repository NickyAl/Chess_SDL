#include "Window.h"
#include "Rect.h"
#include "Background.h"
#include "Pawn.h"
#include <iostream>
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

void pollEvents(char gridTeams[][9], char gridFigures[][9], Window& window,
				Rect* moves, Pawn* pawns,
				Bishop* bishops, Knight* knights,
				Rook* rooks, Queen* queens, King* kings, size_t* rmvFig, char& turn)
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
		for(size_t i = 0; i < 4; i++)
			bishops[i].pollEvents(event, gridTeams, gridFigures, rmvFig, turn);
		for (size_t i = 0; i < 16; i++) //we know have 8 pawns in the team probably gonna have to change to 16 later
			pawns[i].pollEvents(event, gridTeams, gridFigures, rmvFig, turn);
		for (size_t i = 0; i < 4; i++)
			knights[i].pollEvents(event, gridTeams, gridFigures, rmvFig, turn);
		for (size_t i = 0; i < 4; i++)
			rooks[i].pollEvents(event, gridTeams, gridFigures, rmvFig, turn);
		for (size_t i = 0; i < 2; i++)
			queens[i].pollEvents(event, gridTeams, gridFigures, rmvFig, turn);
		for (size_t i = 0; i < 2; i++)
			kings[i].pollEvents(event, gridTeams, gridFigures, rmvFig, turn);
	}
}

int main(int argc, char** argv)
{
	Window window("Chess_sdl", 720, 720);
	Background board(720, 720, 0, 0, "Resources/board2.jpg");

	char gridTeams[9][9]; //starts with all free
	for (size_t i = 0; i < 8; i++)
	{
		if (i != 7 && i != 6 && i != 0 && i != 1)
		{
			for (size_t j = 0; j < 8; j++)
			{
				gridTeams[i][j] = '-';
			}
		}
		else if(i != 0 && i != 1)
		{
			for (size_t j = 0; j < 8; j++)
			{
				gridTeams[i][j] = 'W';
			}
		}
		else
		{
			for (size_t j = 0; j < 8; j++)
			{
				gridTeams[i][j] = 'B';
			}
		}
	}

	char gridFigures[9][9]; //starts with all free

	for (size_t i = 0; i < 8; i++)
	{
		if (i != 7 && i != 6 && i != 0 && i != 1)
		{
			for (size_t j = 0; j < 8; j++)
			{
				gridFigures[i][j] = '-';
			}
		}
		else if (i != 1)
		{
			for (size_t j = 0; j < 8; j++)
			{
				gridFigures[i][j] = 'p';
			}
		}
		else if (i != 6)
		{
			for (size_t j = 0; j < 8; j++)
			{
				gridFigures[i][j] = 'p';
			}
		}
	}

	//black team
	gridFigures[0][0] = 'r'; //rook
	gridFigures[0][7] = 'r';
	gridFigures[0][1] = 'k'; //knight
	gridFigures[0][6] = 'k';
	gridFigures[0][2] = 'b'; //bishop
	gridFigures[0][5] = 'b'; 
	gridFigures[0][3] = 'Q'; //queen
	gridFigures[0][4] = 'K'; //King
	//white team
	gridFigures[7][0] = 'r'; //rook
	gridFigures[7][7] = 'r';
	gridFigures[7][1] = 'k'; //knight
	gridFigures[7][6] = 'k';
	gridFigures[7][2] = 'b'; //bishop
	gridFigures[7][5] = 'b';
	gridFigures[7][3] = 'Q'; //queen
	gridFigures[7][4] = 'K'; //King

	for (size_t i = 0; i < 9; i++)
		gridTeams[8][i] = '/';
	for (size_t i = 0; i < 9; i++)
		gridTeams[i][8] = '/';

	King kings[2];
	kings[0].setW(90);
	kings[0].setH(90);
	kings[0].setX(360);
	kings[0].setY(630);
	kings[0].setTexture("Resources/WhiteKing.png");

	kings[1].setW(90);
	kings[1].setH(90);
	kings[1].setX(360);
	kings[1].setY(0);
	kings[1].setTeam('B');
	kings[1].setTexture("Resources/BlackKing.png");


	Queen queens[2];
	queens[0].setW(90);
	queens[0].setH(90);
	queens[0].setX(270);
	queens[0].setY(630);
	queens[0].setTexture("Resources/WhiteQueen.png");

	queens[1].setW(90);
	queens[1].setH(90);
	queens[1].setX(270);
	queens[1].setY(0);
	queens[1].setTeam('B');
	queens[1].setTexture("Resources/BlackQueen.png");

	Rook rooks[4];
	for (size_t i = 0; i < 4; i++)
	{
		rooks[i].setW(90);
		rooks[i].setH(90);
		rooks[i].setX(0 + (630 * i));
		rooks[i].setY(630);

		if (i > 1)
		{
			rooks[i].setW(90);
			rooks[i].setH(90);
			rooks[i].setX(0 + (630 * (i - 2)));
			rooks[i].setY(0);
			rooks[i].setTeam('B');
			rooks[i].setTexture("Resources/BlackRook.png");
		}
	}

	Knight knights[4];
	for (size_t i = 0; i < 4; i++)
	{
		knights[i].setW(90);
		knights[i].setH(90);
		knights[i].setX(90 + (450 * i));
		knights[i].setY(630);

		if (i > 1)
		{
			knights[i].setW(90);
			knights[i].setH(90);
			knights[i].setX(90 + (450 * (i - 2)));
			knights[i].setY(0);
			knights[i].setTeam('B');
			knights[i].setTexture("Resources/BlackKnight.png");
		}
	}

	Bishop bishops[4];
	for (size_t i = 0; i < 4; i++)
	{
		bishops[i].setW(90);
		bishops[i].setH(90);
		bishops[i].setX(180 + (270 * i));
		bishops[i].setY(630);

		if (i > 1)
		{
			bishops[i].setW(90);
			bishops[i].setH(90);
			bishops[i].setX(180 + (270 * (i - 2)));
			bishops[i].setY(0);
			bishops[i].setTeam('B');
			bishops[i].setTexture("Resources/BlackBishop.png");
		}
	}

	Pawn pawns[16];
	for (size_t i = 0; i < 16; i++)
	{
		pawns[i].setW(90);
		pawns[i].setH(90);
		pawns[i].setX(90 * i);
		pawns[i].setY(540);
		
		if (i > 7)
		{
			pawns[i].setW(90);
			pawns[i].setH(90);
			pawns[i].setX(90 * (i - 8));
			pawns[i].setY(90);
			pawns[i].setTeam('B');
			pawns[i].setTexture("Resources/BlackPawn.png");
		}
	}

	Rect posMoves[64];
	for (size_t i = 0; i < 64; i++)
	{
		posMoves[i].setW(50);
		posMoves[i].setH(50);
		posMoves[i].setR(100);
		posMoves[i].setG(140);
		posMoves[i].setB(100);
		posMoves[i].setA(150);
	}

	size_t rmvFig[3]; //coordinates for removing the figure on them
	rmvFig[0] = -1; // coord
	rmvFig[1] = -1; // coord
	rmvFig[2] = -1; // color ascii code of 'W' and 'B'

	char turn = 'W';

	while (!window.isClosed())
	{
		pollEvents(gridTeams, gridFigures, window, posMoves, pawns, bishops, knights, rooks, queens, kings, rmvFig, turn);
		board.draw();

		//DRAWING THE KINGS AND THEIR POSSIABLE MOVES
		for (size_t i = 0; i < 2; i++)
		{
			kings[i].draw();
			if (kings[i].getMarked())
			{
				posMoves[0].setX(kings[i].getX() + 20);
				posMoves[0].setY(kings[i].getY() - 70);
				posMoves[0].draw();

				posMoves[1].setX(kings[i].getX() + 20);
				posMoves[1].setY(kings[i].getY() + 110);
				posMoves[1].draw();

				posMoves[2].setX(kings[i].getX() - 70);
				posMoves[2].setY(kings[i].getY() + 20);
				posMoves[2].draw();

				posMoves[3].setX(kings[i].getX() + 110);
				posMoves[3].setY(kings[i].getY() + 20);
				posMoves[3].draw();

				posMoves[4].setX(kings[i].getX() - 70);
				posMoves[4].setY(kings[i].getY() - 70);
				posMoves[4].draw();

				posMoves[5].setX(kings[i].getX() + 110);
				posMoves[5].setY(kings[i].getY() + 110);
				posMoves[5].draw();

				posMoves[6].setX(kings[i].getX() + 110);
				posMoves[6].setY(kings[i].getY() - 70);
				posMoves[6].draw();

				posMoves[7].setX(kings[i].getX() - 70);
				posMoves[7].setY(kings[i].getY() + 110);
				posMoves[7].draw();
			}
		}

		//DRAWING THE QUEENS AND THEIR POSSIABLE MOVES
		for (size_t i = 0; i < 2; i++)
		{
			queens[i].draw();

			if (queens[i].getMarked())
			{
				for (size_t j = 0, k = 0; j < 64; j += 8, k++)
				{
					posMoves[j].setX(queens[i].getX() + 20);
					posMoves[j].setY(queens[i].getY() - 70 - (90 * k));
					posMoves[j].draw();

					posMoves[j + 1].setX(queens[i].getX() + 20);
					posMoves[j + 1].setY(queens[i].getY() + 110 + (90 * k));
					posMoves[j + 1].draw();

					posMoves[j + 2].setX(queens[i].getX() - 70 - (90 * k));
					posMoves[j + 2].setY(queens[i].getY() + 20);
					posMoves[j + 2].draw();

					posMoves[j + 3].setX(queens[i].getX() + 110 + (90 * k));
					posMoves[j + 3].setY(queens[i].getY() + 20);
					posMoves[j + 3].draw();

					posMoves[j + 4].setX(queens[i].getX() - 70 - (90 * k));
					posMoves[j + 4].setY(queens[i].getY() - 70 - (90 * k));
					posMoves[j + 4].draw();

					posMoves[j + 5].setX(queens[i].getX() + 110 + (90 * k));
					posMoves[j + 5].setY(queens[i].getY() + 110 + (90 * k));
					posMoves[j + 5].draw();

					posMoves[j + 6].setX(queens[i].getX() + 110 + (90 * k));
					posMoves[j + 6].setY(queens[i].getY() - 70 - (90 * k));
					posMoves[j + 6].draw();

					posMoves[j + 7].setX(queens[i].getX() - 70 - (90 * k));
					posMoves[j + 7].setY(queens[i].getY() + 110 + (90 * k));
					posMoves[j + 7].draw();
				}
			}
		}

		//DRAWING THE ROOKS AND THEIR POSSIABLE MOVES
		for (size_t i = 0; i < 4; i++)
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

		//DRAWING THE KNIGHTS AND THEIR POSSIABLE MOVES
		for (size_t i = 0; i < 4; i++)
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

		//DRAWING THE BISHOPS AND THEIR POSSIABLE MOVES
		for (size_t i = 0; i < 4; i++)
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

		//DRAWING THE PAWNS AND THEIR POSSIABLE MOVES
		for (size_t i = 0; i < 16; i++)
		{
			pawns[i].draw();

			if (pawns[i].getMarked())
			{
				if (pawns[i].getTeam() == 'W')
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
				else
				{
					for (size_t j = 0; j < 2; j++)
					{
						posMoves[j].setX(pawns[i].getX() + 20);
						posMoves[j].setY(pawns[i].getY() + 110 + (90 * j));

						posMoves[j].draw();

						if (pawns[i].getY() != 90)
							break;
					}
				}
			}
		}

		//CHECKING IF WE NEED TO REMOVE A FIGURE FROM THE BOARD
		if (rmvFig[0] != -1 && rmvFig[1] != -1)
		{
			for (size_t i = 0; i < 16; i++)
			{
				if (pawns[i].getTeam() == rmvFig[2]) //using the ascii code of 'W'/'B'
				{
					if (pawns[i].getX() / 90 == rmvFig[1] &&
						pawns[i].getY() / 90 == rmvFig[0])
					{
						pawns[i].setX(1720);
						pawns[i].setY(1720);
						break;
					}
				}
			}

			for (size_t i = 0; i < 4; i++)
			{
				if (rooks[i].getTeam() == rmvFig[2]) //using the ascii code of 'W'/'B'
				{
					if (rooks[i].getX() / 90 == rmvFig[1] &&
						rooks[i].getY() / 90 == rmvFig[0])
					{
						rooks[i].setX(1720);
						rooks[i].setY(1720);
						break;
					}
				}
			}

			for (size_t i = 0; i < 4; i++)
			{
				if (knights[i].getTeam() == rmvFig[2]) //using the ascii code of 'W'/'B'
				{
					if (knights[i].getX() / 90 == rmvFig[1] &&
						knights[i].getY() / 90 == rmvFig[0])
					{
						knights[i].setX(1720);
						knights[i].setY(1720);
						break;
					}
				}
			}

			for (size_t i = 0; i < 4; i++)
			{
				if (bishops[i].getTeam() == rmvFig[2]) //using the ascii code of 'W'/'B'
				{
					if (bishops[i].getX() / 90 == rmvFig[1] &&
						bishops[i].getY() / 90 == rmvFig[0])
					{
						bishops[i].setX(1720);
						bishops[i].setY(1720);
						break;
					}
				}
			}

			for (size_t i = 0; i < 2; i++)
			{
				if (kings[i].getTeam() == rmvFig[2]) //using the ascii code of 'W'/'B'
				{
					if (kings[i].getX() / 90 == rmvFig[1] &&
						kings[i].getY() / 90 == rmvFig[0])
					{
						kings[i].setX(1720);
						kings[i].setY(1720);
						break;
					}
				}
			}

			for (size_t i = 0; i < 2; i++)
			{
				if (queens[i].getTeam() == rmvFig[2]) //using the ascii code of 'W'/'B'
				{
					if (queens[i].getX() / 90 == rmvFig[1] &&
						queens[i].getY() / 90 == rmvFig[0])
					{
						queens[i].setX(1720);
						queens[i].setY(1720);
						break;
					}
				}
			}

			rmvFig[0] = -1;
			rmvFig[1] = -1;
		}

		window.clear();
	}

	return 0;
}