#pragma once
#include <string>
#include <SDL.h>

class Window
{
private:
	std::string title;
	int _width = 800;
	int _height = 600;

	bool _closed = false;

	SDL_Window* _window = nullptr;

	//int _markedX;
	//int _markedY;

	bool init();
public:
	static SDL_Renderer* renderer;

public:
	Window(const std::string& newTitle, int newWidth, int newHeight);
	~Window();

	bool isClosed()const { return this->_closed; }

	void pollEvents(SDL_Event& event);
	void clear() const; //"means to put stuff onto the screen" - youtube dude

	//int getMarkedX()const { return _markedX; }
	//int getMarkedY()const { return _markedY; }
};