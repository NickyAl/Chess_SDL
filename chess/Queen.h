#pragma once
#include "Figure.h"

class Queen : public Figure
{
private:

public:
	Queen();
	Queen(int w, int h, int x, int y, int r, int g, int b, int a, bool marked, char team);
	Queen(int w, int h, int x, int y, const std::string& image_path, bool marked, char team);
	~Queen();

	void pollEvents(SDL_Event& event, char gridTeams[][9], size_t* rmvFig);
};