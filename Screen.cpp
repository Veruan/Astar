#include "Screen.h"

Screen::Screen()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 255);
	SDL_RenderClear(this->renderer);

	SDL_RenderPresent(this->renderer);

	SDL_Delay(3000);
}


Screen::~Screen()
{

}