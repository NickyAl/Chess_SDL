#pragma once
#include "Figure.h"
#include "Window.h"
#include <string>

class Pawn : public Figure
{
private:

public:
	Pawn();
	Pawn(int w, int h, int x, int y, int r, int g, int b, int a, bool marked, char team);
	Pawn(int w, int h, int x, int y, const std::string& image_path, bool marked, char team);
	~Pawn();

	void pollEvents(SDL_Event& event, char gridTeams[][9], char gridFigures[][9], size_t* rmvFig, char& turn);
};