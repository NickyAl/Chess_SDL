#pragma once
#include "Figure.h"

class Rook : public Figure
{
private:

public:
	Rook();
	Rook(int w, int h, int x, int y, int r, int g, int b, int a, bool marked);
	Rook(int w, int h, int x, int y, const std::string& image_path, bool marked);
	~Rook();

	void pollEvents(SDL_Event& event, char grid[][8]);
};