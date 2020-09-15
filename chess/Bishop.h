#pragma once
#include "Window.h"
#include <string>
#include "Figure.h"

class Bishop : public Figure
{
private:

public:
	Bishop();
	Bishop(int w, int h, int x, int y, int r, int g, int b, int a, bool marked);
	Bishop(int w, int h, int x, int y, const std::string& image_path, bool marked);
	~Bishop();

	void pollEvents(SDL_Event& event, bool grid[][8]);
};