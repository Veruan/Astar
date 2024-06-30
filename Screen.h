#ifndef ASTAR_SCREEN_H
#define ASTAR_SCREEN_H

#include "SDL.h"

class Screen
{
	private:

		SDL_Window *window;
		SDL_Renderer  *renderer;

	public:

		Screen(int width, int height);

		~Screen();
		
};

#endif