#include "Window.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Renderer* Window::renderer;

Window::Window(const std::string& newTitle, int newWidth, int newHeight) :
	title(newTitle), _width(newWidth), _height(newHeight)
{
	this->_closed = !init();
}

Window::~Window()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->_window);
	IMG_Quit();
	SDL_Quit();
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO)) //ONLY VIDEO PORTION IF ADDING AUDIO MUST CHANGE
	{
		std::cerr << "Failed to init SDL.\n";
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) //png or jpg images
	{
		std::cerr << "Failed to init SDL_image\n";
		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cerr << "Failed to init SDL_ttf\n";
		return false;
	}

	this->_window = SDL_CreateWindow(this->title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->_width, this->_height, 0);

	if (this->_window == nullptr)
	{
		std::cerr << "Failed to create window\n";
		return 0;
	}

	this->renderer = SDL_CreateRenderer(this->_window, -1,
		SDL_RENDERER_ACCELERATED); //Can change to vsynced to cap the fps at 60

	if (renderer == nullptr)
	{
		std::cerr << "Failed to create renderer\n";
		return false;
	}

	return true;
}

void Window::pollEvents(SDL_Event& event)
{
	int x = 10000, y = 10000;
	switch (event.type)
	{
	case SDL_QUIT:
		this->_closed = true;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			this->_closed = true;
			break;

		case SDLK_w:
			std::cout << "You clicked \"W\"\n";
			break;
		case SDLK_a:
			std::cout << "You clicked \"A\"\n";
			break;
		case SDLK_s:
			std::cout << "You clicked \"S\"\n";
			break;
		case SDLK_d:
			std::cout << "You clicked \"D\"\n";
			break;

		default:
			break;
		}

	case SDL_MOUSEMOTION:
		std::cout << event.motion.x << ", " << event.motion.y << '\n';
		break;

	default:
		break;
	}
}

void Window::clear() const
{
	SDL_RenderPresent(this->renderer);

	SDL_SetRenderDrawColor(this->renderer, 100, 80, 200, 255); //renderer R G B Opacity
	SDL_RenderClear(this->renderer);
}
