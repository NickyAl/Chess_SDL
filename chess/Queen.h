#pragma once
#include "Figure.h"

class Queen : public Figure
{
private:

public:
	Queen();
	Queen(int w, int h, int x, int y, int r, int g, int b, int a, bool marked);
	Queen(int w, int h, int x, int y, const std::string& image_path, bool marked);
	~Queen();

	void pollEvents(SDL_Event& event, char grid[][9]);
};