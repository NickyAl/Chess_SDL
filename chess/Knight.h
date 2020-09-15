#pragma once
#include "Figure.h"

class Knight : public Figure
{
private:

public:
	Knight();
	Knight(int w, int h, int x, int y, int r, int g, int b, int a, bool marked);
	Knight(int w, int h, int x, int y, const std::string& image_path, bool marked);
	~Knight();

	void pollEvents(SDL_Event& event, char grid[][8]);
};