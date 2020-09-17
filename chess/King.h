#pragma once
#include "Figure.h"

class King : public Figure
{
private:

public:
	King();
	King(int w, int h, int x, int y, int r, int g, int b, int a, bool marked, char team);
	King(int w, int h, int x, int y, const std::string& image_path, bool marked, char team);
	~King();

	void pollEvents(SDL_Event& event, char gridTeams[][9], char gridFigures[][9], size_t* rmvFig, char& turn);
};