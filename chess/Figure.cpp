#include "Figure.h"
#include <SDL_image.h>
#include <iostream>
#include <string>

void Figure::draw() const
{
	SDL_Rect pawn = { _x, _y, _w, _h };

	if (_texture)
	{
		SDL_RenderCopy(Window::renderer, _texture, nullptr, &pawn);
	}
	else
	{
		SDL_SetRenderDrawColor(Window::renderer, _r, _g, _b, _a);
		SDL_RenderFillRect(Window::renderer, &pawn);
	}
}

SDL_Texture* Figure::LoadTexture(std::string filepath)
{
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurf = IMG_Load(filepath.c_str());

	if (loadedSurf == nullptr)
	{
		std::cerr << "Failed to load pawn texture\n";
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(Window::renderer, loadedSurf);
		if (newTexture == nullptr)
		{
			std::cerr << "Failed to create texture for pawn\n";
		}
		SDL_FreeSurface(loadedSurf);
	}

	return newTexture;
}

bool Figure::isUnguarded(char gridTeams[][9], char gridFigures[][9], int x, int y, char team)
{
	bool gridGuarded[8][8];
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			gridGuarded[i][j] = false;
		}
	}

	//determines which is the opposite team
	char otherTeam = 'W';
	if (team == otherTeam)
	{
		otherTeam = 'B';
	}

	int k = 0, l = 0;

	//determines which squares are protected by figures of the opposite team
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (gridTeams[i][j] == otherTeam)
			{
				switch (gridFigures[i][j])
				{
				case 'p':					//WHERE PAWNS PROTECT
					if (otherTeam == 'W')
					{
						if (i != 0)
						{
							if (j != 7)
								gridGuarded[i - 1][j + 1] = true;
							if (j != 0)
								gridGuarded[i - 1][j - 1] = true;
						}
					}
					else
					{
						if (i != 7)
						{
							if (j != 7)
								gridGuarded[i + 1][j + 1] = true;
							if (j != 0)
								gridGuarded[i + 1][j - 1] = true;
						}
					}

					break;

				case 'r':					//WHERE ROOKS PROTECT
					if (i > 0)
					{
						gridGuarded[i - 1][j] = true;
					}
					if (i < 7)
					{
						gridGuarded[i + 1][j] = true;
					}
					if (j > 0)
					{
						gridGuarded[i][j - 1] = true;
					}
					if (j < 7)
					{
						gridGuarded[i][j + 1] = true;
					}
					
					k = j + 1;

					while (k - 1 < 7 && gridFigures[i][k] == '-')
					{
						gridGuarded[i][k] = true;
						k++;
						if (k - 1 < 7 && gridFigures[i][k + 1] != '-')
						{
							gridGuarded[i][k + 1] = true;
						}
					}

					k = j - 1;
		
					while (k + 1 > 0 && gridFigures[i][k] == '-')
					{
						gridGuarded[i][k] = true;
						k--;
						if (k + 1 > 0 && gridFigures[i][k] != '-')
						{
							gridGuarded[i][k] = true;
						}
					}
					k = i + 1;
		
					while (k - 1 < 7 && gridFigures[k][j] == '-')
					{
						gridGuarded[k][j] = true;
						k++;
						if (k - 1 < 7 && gridFigures[k][j] != '-')
						{
							gridGuarded[k][j] = true;
						}
					}
					k = i - 1;
	
					while (k + 1 > 0 && gridFigures[k][j] == '-')
					{
						gridGuarded[k][j] = true;
						k--;
						if (k + 1 > 0 && gridFigures[k][j] != '-')
						{
							gridGuarded[k][j] = true;
						}
					}
	
					break;

				case 'b':			//WHERE BISHOP PROTECT

					if (i > 0 && j > 0)
					{
						gridGuarded[i - 1][j - 1] = true;
					}
					if (i < 7 && j < 7)
					{
						gridGuarded[i + 1][j + 1] = true;
					}
					if (j > 0 && i < 7)
					{
						gridGuarded[i + 1][j - 1] = true;
					}
					if (j < 7 && i > 0)
					{
						gridGuarded[i - 1][j + 1] = true;
					}

					k = i + 1;
					l = j + 1;

					while (k - 1 < 7 && l - 1 < 7 && gridFigures[k][l] == '-')
					{
						gridGuarded[k][l] = true;
						k++;
						l++;
						if (k - 1 < 7 && l - 1 < 7 && gridFigures[k][l] != '-')
						{
							gridGuarded[k][l] = true;
						}
					}
					k = i + 1;
					l = j - 1;

					while (k - 1 < 7 && l + 1 > 0 && gridFigures[k][l] == '-')
					{
						gridGuarded[k][l] = true;
						k++;
						l--;
						if (k -1 < 7 && l + 1 > 0 && gridFigures[k][l] != '-')
						{
							gridGuarded[k][l] = true;
						}
					}
					k = i - 1;
					l = j + 1;

					while (k + 1 > 0 && l - 1 < 7 && gridFigures[k][l] == '-')
					{
						gridGuarded[k][l] = true;
						k--;
						l++;
						if (k + 1 > 0 && l + 1 < 7 && gridFigures[k][l] != '-')
						{
							gridGuarded[k][l] = true;
						}
					}
					k = i - 1;
					l = j - 1;

					while (k + 1 > 0 && l + 1 > 0 && gridFigures[k][l] == '-')
					{
						gridGuarded[k][l] = true;
						k--;
						l--;
						if (l + 1 > 0 && k + 1 > 0 && gridFigures[k][l] != '-')
						{
							gridGuarded[k][l] = true;
						}
					}

					break;

				case 'Q':					//WHERE QUEEN PROTECT
					if (i > 0)
					{
						gridGuarded[i - 1][j] = true;
					}
					if (i < 7)
					{
						gridGuarded[i + 1][j] = true;
					}
					if (j > 0)
					{
						gridGuarded[i][j - 1] = true;
					}
					if (j < 7)
					{
						gridGuarded[i][j + 1] = true;
					}
					if (i > 0 && j > 0)
					{
						gridGuarded[i - 1][j - 1] = true;
					}
					if (i < 7 && j < 7)
					{
						gridGuarded[i + 1][j + 1] = true;
					}
					if (j > 0 && i < 7)
					{
						gridGuarded[i + 1][j - 1] = true;
					}
					if (j < 7 && i > 0)
					{
						gridGuarded[i - 1][j + 1] = true;
					}

					k = j + 1;

					while (k - 1 < 7 && gridFigures[i][k] == '-')
					{
						gridGuarded[i][k] = true;
						k++;
						if (k - 1 < 7 && gridFigures[i][k + 1] != '-')
						{
							gridGuarded[i][k + 1] = true;
						}
					}

					k = j - 1;

					while (k + 1 > 0 && gridFigures[i][k] == '-')
					{
						gridGuarded[i][k] = true;
						k--;
						if (k + 1 > 0 && gridFigures[i][k] != '-')
						{
							gridGuarded[i][k] = true;
						}
					}
					k = i + 1;

					while (k - 1 < 7 && gridFigures[k][j] == '-')
					{
						gridGuarded[k][j] = true;
						k++;
						if (k - 1 < 7 && gridFigures[k][j] != '-')
						{
							gridGuarded[k][j] = true;
						}
					}
					k = i - 1;

					while (k + 1 > 0 && gridFigures[k][j] == '-')
					{
						gridGuarded[k][j] = true;
						k--;
						if (k + 1 > 0 && gridFigures[k][j] != '-')
						{
							gridGuarded[k][j] = true;
						}
					}

					k = i + 1;
					l = j + 1;

					while (k - 1 < 7 && l - 1 < 7 && gridFigures[k][l] == '-')
					{
						gridGuarded[k][l] = true;
						k++;
						l++;
						if (k - 1 < 7 && l - 1 < 7 && gridFigures[k][l] != '-')
						{
							gridGuarded[k][l] = true;
						}
					}
					k = i + 1;
					l = j - 1;

					while (k - 1 < 7 && l + 1 > 0 && gridFigures[k][l] == '-')
					{
						gridGuarded[k][l] = true;
						k++;
						l--;
						if (k - 1 < 7 && l + 1 > 0 && gridFigures[k][l] != '-')
						{
							gridGuarded[k][l] = true;
						}
					}
					k = i - 1;
					l = j + 1;

					while (k + 1 > 0 && l - 1 < 7 && gridFigures[k][l] == '-')
					{
						gridGuarded[k][l] = true;
						k--;
						l++;
						if (k + 1 > 0 && l + 1 < 7 && gridFigures[k][l] != '-')
						{
							gridGuarded[k][l] = true;
						}
					}
					k = i - 1;
					l = j - 1;

					while (k + 1 > 0 && l + 1 > 0 && gridFigures[k][l] == '-')
					{
						gridGuarded[k][l] = true;
						k--;
						l--;
						if (l + 1 > 0 && k + 1 > 0 && gridFigures[k][l] != '-')
						{
							gridGuarded[k][l] = true;
						}
					}
					break;

				case 'k':			//WHERE KNIGHT PROTECT
					if(i - 1 > 0 && j + 2 < 7)
						gridGuarded[i - 1][j + 2] = true;

					if(i + 1 <= 7 && j + 2 <= 7)
						gridGuarded[i + 1][j + 2] = true;

					if(i + 2 <= 7 && j + 1 <= 7)
						gridGuarded[i + 2][j + 1] = true;

					if(i + 2 <= 7 && j - 1 >= 0)
						gridGuarded[i + 2][j - 1] = true;

					if(i + 1 <= 7 && j - 2 >= 0)
						gridGuarded[i + 1][j - 2] = true;

					if(i - 1 >= 0 && j - 2 >= 0)
						gridGuarded[i - 1][j - 2] = true;

					if(i - 2 >= 0 && j - 1 >= 0)
						gridGuarded[i - 2][j - 1] = true;

					if(i - 2 >= 0 && j + 1 <= 7)
						gridGuarded[i - 2][j + 1] = true;

					break;

				case 'K':			//WHERE KING PROTECT
					if(i + 1 <= 7)
						gridGuarded[i + 1][j] = true;
					
					if(i - 1 >= 0)
						gridGuarded[i - 1][j] = true;
					
					if(j + 1 <= 7)
						gridGuarded[i][j + 1] = true;
					
					if(j - 1 >= 0)
						gridGuarded[i][j - 1] = true;
					
					if(i + 1 <= 7 && j + 1 <= 7)
						gridGuarded[i + 1][j + 1] = true;
					
					if(i - 1 >= 0 && j - 1 >= 0)
						gridGuarded[i - 1][j - 1] = true;
					
					if(i + 1 <= 7 && j - 1 >= 0)
						gridGuarded[i + 1][j - 1] = true;
					
					if(i - 1 >= 0 && j + 1 <= 7)
						gridGuarded[i - 1][j + 1] = true;

				default:
					break;
				}
			}
		}
	}

	//Printing the grid in the console for debuging
	//for (size_t i = 0; i < 8; i++)
	//{
	//	for (size_t j = 0; j < 8; j++)
	//	{
	//		std::cout << gridGuarded[i][j] << " ";
	//	}
	//	std::cout << "\n";
	//}

	//RETURNS 1 if the sqr is free and the king can go there returns 0 if any figure from the other team is protecting the sqr and the king cant go there
	return !(gridGuarded[y][x]);
}
