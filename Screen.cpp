#include "Screen.h"

Screen::Screen() : rect_size_x(10), rect_size_y(10), width(1920), height(1080)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window = SDL_CreateWindow("A* algorithm visualisation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	this->set_color(BLACK);
	SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(this->renderer);
}


Screen::Screen(int width, int height) : rect_size_x(10), rect_size_y(10), width(width), height(height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window = SDL_CreateWindow("A* algorithm visualisation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	this->set_color(BLACK);
	SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(this->renderer);
}


Screen::~Screen()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	SDL_Quit();
}


void Screen::set_square_size(const Physical& physical)
{
	this->rect_size_x = this->width / physical.get_size_x();
	this->rect_size_y = this->height / physical.get_size_y();
}


void Screen::set_color(const color_t& color)
{
	SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}


void Screen::set_alg_color(const std::pair<int, int>& position, const Physical& physical, std::unique_ptr<std::unique_ptr<bool[]>[]>& added,
	std::unique_ptr<std::unique_ptr<bool[]>[]>& visited)
{
	switch (physical.get_grid(position))
	{
		case START:
		case END:
			this->set_color(BLUE);
			break;

		case WALL:
			this->set_color(BLACK);
			break;

		case EMPTY:

			if (visited[position.second][position.first])
			{
				this->set_color(RED);
				break;
			}

			if (added[position.second][position.first])
			{
				this->set_color(GREEN);
				break;
			}

			this->set_color(WHITE);
			break;
	}
}


void Screen::draw_grid(const Physical& physical, std::unique_ptr<std::unique_ptr<bool[]>[]>& added,
	std::unique_ptr<std::unique_ptr<bool[]>[]>& visited)
{
	this->set_square_size(physical);

	for (int i = 0; i < physical.get_size_y(); i++)
	{
		for (int j = 0; j < physical.get_size_x(); j++) 
		{
			this->set_alg_color({ j, i }, physical, added, visited);

			SDL_Rect fillRect = { j * this->rect_size_x, i * this->rect_size_y, this->rect_size_x, this->rect_size_y };
			SDL_RenderFillRect(this->renderer, &fillRect);

			this->set_color(BLACK);
			SDL_RenderDrawRect(this->renderer, &fillRect);
		}
	}

	SDL_RenderPresent(this->renderer);

	SDL_Delay(10);
}


void Screen::draw_path(const Physical& physical, std::vector<std::pair<int, int>>& path)
{
	this->set_color(WHITE);

	SDL_Rect fillRect = { 0, 0, this->width, this->height };
	SDL_RenderFillRect(this->renderer, &fillRect);

	this->set_color(BLACK);
	for (int i = 0; i < physical.get_size_y(); i++)
	{
		for (int j = 0; j < physical.get_size_x(); j++)
		{
			SDL_Rect fillRect = { j * this->rect_size_x, i * this->rect_size_y, this->rect_size_x, this->rect_size_y };
			if (physical.get_grid({ j, i }) == WALL)
				SDL_RenderFillRect(this->renderer, &fillRect);

			else
				SDL_RenderDrawRect(this->renderer, &fillRect);

		}
	}

	this->set_color(BLUE);
	for (int i = 0; i < path.size(); i++)
	{
		SDL_Rect fillRect = { path[i].first * this->rect_size_x, path[i].second * this->rect_size_y, this->rect_size_x, this->rect_size_y };
		SDL_RenderFillRect(this->renderer, &fillRect);
	}

	SDL_RenderPresent(this->renderer);

	SDL_Delay(5000);
}