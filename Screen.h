#ifndef ASTAR_SCREEN_H
#define ASTAR_SCREEN_H

#include <vector>
#include <memory>

#include "SDL.h"
#include "Physical.h"

using color_t = struct
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

// Define some global colors
const color_t RED = { 0xFF, 0x00, 0x00, 0xFF };
const color_t GREEN = { 0x00, 0xFF, 0x00, 0xFF };
const color_t BLUE = { 0x00, 0x00, 0xFF, 0xFF };
const color_t WHITE = { 0xFF, 0xFF, 0xFF, 0xFF };
const color_t BLACK = { 0x00, 0x00, 0x00, 0xFF };


class Screen
{
	private:

		int rect_size_x;
		int rect_size_y;

		int width;
		int height;

		SDL_Window *window;
		SDL_Renderer  *renderer;

	public:

		Screen();

		Screen(int width, int height);

		~Screen();

		void set_square_size(const Physical& physical);

		void set_color(const color_t& color);

		void set_alg_color(const std::pair<int, int>& position, const Physical& physical, std::unique_ptr<std::unique_ptr<bool[]>[]>& added,
			std::unique_ptr<std::unique_ptr<bool[]>[]>& visited);

		void draw_grid(const Physical& physical, std::unique_ptr<std::unique_ptr<bool[]>[]>& added,
			std::unique_ptr<std::unique_ptr<bool[]>[]>& visited);

		void draw_path(const Physical& physical, std::vector<std::pair<int, int>>& path);

};

#endif