#ifndef ASTAR_SCREEN_H
#define ASTAR_SCREEN_H

#include <vector>
#include <string>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Physical.h"

enum OPTIONS
{
	PUT_EMPTY = '0',
	PUT_WALL = '1',
	PUT_START = '2',
	PUT_END = '3'
};


using color_t = struct
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};


const color_t RED = { 0xFF, 0x00, 0x00, 0xFF };
const color_t GREEN = { 0x00, 0xFF, 0x00, 0xFF };
const color_t BLUE = { 0x00, 0x00, 0xFF, 0xFF };
const color_t WHITE = { 0xFF, 0xFF, 0xFF, 0xFF };
const color_t BLACK = { 0x00, 0x00, 0x00, 0xFF };
const color_t YELLOW = { 0xFF, 0xFF, 0x00, 0xFF };
const color_t MAGENTA = { 0xFF, 0x00, 0xFF, 0xFF };
const color_t BUFF = { 0xC6, 0x9F, 0x89, 0xFF };
const color_t BURGUNDY = { 0x93, 0x03, 0x2E, 0xFF };
const color_t CARRIBEAN_CURRENT = { 0x02, 0x6C, 0x7C, 0xFF };

class Screen
{
	private:

		int width;
		int height;

		int rect_size_x;
		int rect_size_y;

		SDL_Window *window;
		SDL_Renderer  *renderer;

		char current_option;

	public:

		Screen();

		Screen(int width, int height);

		~Screen();

		void set_square_size(const Physical& physical);

		void set_color(const color_t& color);

		void menu();

		SDL_Texture* render_text(const std::string& message, TTF_Font* font, SDL_Color color);

		void idle(Physical& physical, bool *over);

		void event_handler(SDL_Event* event, Physical& physical, bool* start, bool* over);

		void handle_mouse(SDL_Event* event, Physical& physical);

		void handle_keyboard(SDL_Event* event, bool* start, bool* over);

		void extract_square_coords(int* x, int* y);

		void draw_grid_idle(const Physical& physical);

		void set_alg_color(const std::pair<int, int>& position, const Physical& physical, std::unique_ptr<std::unique_ptr<bool[]>[]>& added,
			std::unique_ptr<std::unique_ptr<bool[]>[]>& visited);

		void draw_grid(const Physical& physical, std::unique_ptr<std::unique_ptr<bool[]>[]>& added,
			std::unique_ptr<std::unique_ptr<bool[]>[]>& visited);

		void draw_path(const Physical& physical, std::vector<std::pair<int, int>>& path);

};

#endif