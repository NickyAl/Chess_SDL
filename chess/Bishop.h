#pragma once
#include "Window.h"
#include <string>
#include "Figure.h"

class Bishop : public Figure
{
private:

public:
	Bishop();
	Bishop(int w, int h, int x, int y, int r, int g, int b, int a, bool marked, char team);
	Bishop(int w, int h, int x, int y, const std::string& image_path, bool marked, char team);
	~Bishop();

	void pollEvents(SDL_Event& event, char gridTeams[][9], size_t* rmvFig);
};