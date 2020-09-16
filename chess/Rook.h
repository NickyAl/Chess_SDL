#pragma once
#include "Figure.h"

class Rook : public Figure
{
private:

public:
	Rook();
	Rook(int w, int h, int x, int y, int r, int g, int b, int a, bool marked, char team);
	Rook(int w, int h, int x, int y, const std::string& image_path, bool marked, char team);
	~Rook();

	void pollEvents(SDL_Event& event, char gridTeams[][9], size_t* rmvFig);
};