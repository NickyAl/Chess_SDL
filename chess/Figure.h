#pragma once
#include "Window.h"

//MOTHER CLASS FOR ALL THE FIGURES
class Figure
{
protected:
	int _w, _h;				//Width and Height
	int _x, _y;				//Coordinates
	int _r, _g, _b, _a;		//Color if there is no texture
	SDL_Texture* _texture;  //Texture (2D image for the figure)

	bool _marked = false;	//If the user has clicked on the figure's square

	char _team;

public:
	void draw()const;
	
	SDL_Texture* LoadTexture(std::string filepath);

	bool isUnguarded(char gridTeams[][9], char gridFigures[][9], int x, int y, char team);
	
	//SETTERS AND GETTERS

	void setW(int w) { _w = w; }
	int getW()const { return _w; }

	void setH(int h) { _h = h; }
	int getH()const { return _h; }

	void setX(int x) { _x = x; }
	int getX()const { return _x; }

	void setY(int y) { _y = y; }
	int getY()const { return _y; }

	void setMarked(bool marked) { _marked = marked; }
	bool getMarked()const { return _marked; }

	void setTeam(char team) { _team = team; }
	char getTeam()const { return _team; }

	void setTexture(const char* filepath) { _texture = LoadTexture(filepath); }
};