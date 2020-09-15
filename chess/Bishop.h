#pragma once
#include "Window.h"
#include <string>
#include "Figure.h"

class Bishop : public Figure
{
//private:
//	int _w, _h;
//	int _x, _y;
//	int _r, _g, _b, _a;
//	SDL_Texture* _texture;
//
//	bool _marked = false;

public:
	Bishop();
	Bishop(int w, int h, int x, int y, int r, int g, int b, int a, bool marked);
	Bishop(int w, int h, int x, int y, const std::string& image_path, bool marked);
	~Bishop();

	void pollEvents(SDL_Event& event);

	//void draw()const;

	//SDL_Texture* LoadTexture(std::string filepath);

	//SETTERS AND GETTERS

	//void setW(int w) { _w = w; }
	//int getW()const { return _w; }

	//void setH(int h) { _h = h; }
	//int getH()const { return _h; }

	//void setX(int x) { _x = x; }
	//int getX()const { return _x; }

	//void setY(int y) { _y = y; }
	//int getY()const { return _y; }

	//void setMarked(bool marked) { _marked = marked; }
	//bool getMarked()const { return _marked; }
};