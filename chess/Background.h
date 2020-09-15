#pragma once
#include "Window.h"
#include <string>

class Background
{
private:
	int _w, _h;
	int _x, _y;
	int _r, _g, _b, _a;
	SDL_Texture* _texture;

public:
	Background(int w, int h, int x, int y, int r, int g, int b, int a);
	Background(int w, int h, int x, int y, const std::string& image_path);
	~Background();

	void draw()const;
};
