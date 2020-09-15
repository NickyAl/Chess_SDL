#include "Figure.h"
#include <SDL_image.h>
#include <iostream>
#include <string>

void Figure::draw() const
{
	SDL_Rect pawn = { _x, _y, _w, _h };

	if (_texture)
	{
		SDL_RenderCopy(Window::renderer, _texture, nullptr, &pawn);
	}
	else
	{
		SDL_SetRenderDrawColor(Window::renderer, _r, _g, _b, _a);
		SDL_RenderFillRect(Window::renderer, &pawn);
	}
}

SDL_Texture* Figure::LoadTexture(std::string filepath)
{
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurf = IMG_Load(filepath.c_str());

	if (loadedSurf == nullptr)
	{
		std::cerr << "Failed to load pawn texture\n";
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(Window::renderer, loadedSurf);
		if (newTexture == nullptr)
		{
			std::cerr << "Failed to create texture for pawn\n";
		}
		SDL_FreeSurface(loadedSurf);
	}

	return newTexture;
}