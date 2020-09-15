#pragma once
#include "Window.h"
#include <string>

class Rect
{
private:
	int _w, _h;
	int _x, _y;
	int _r, _g, _b, _a;

public:
	Rect();
	Rect(int w, int h, int x, int y, int r, int g, int b, int a);
	~Rect();

	void draw()const;
	void pollEvents(SDL_Event& event);

	//SETTERS AND GETTERS
	void setW(int w) { _w = w; }
	int getW()const { return _w; }

	void setH(int h) { _h = h; }
	int getH()const { return _h; }

	void setX(int x) { _x = x; }
	int getX()const { return _x; }

	void setY(int y) { _y = y; }
	int getY()const { return _y; }

	void setR(int r) { _r = r; }
	int getR()const { return _r; }

	void setG(int g) { _g = g; }
	int getG()const { return _g; }

	void setB(int b) { _b = b; }
	int getB()const { return _b; }

	void setA(int a) { _a = a; }
	int getA()const { return _a; }
};