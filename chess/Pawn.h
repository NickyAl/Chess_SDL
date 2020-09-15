#pragma once
#include "Figure.h"
#include "Window.h"
#include <string>

class Pawn : public Figure
{
private:

public:
	Pawn();
	Pawn(int w, int h, int x, int y, int r, int g, int b, int a, bool marked);
	Pawn(int w, int h, int x, int y, const std::string& image_path, bool marked);
	~Pawn();

	void pollEvents(SDL_Event& event, char grid[][8]);
};