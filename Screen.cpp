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


void Screen::menu()
{
	if (TTF_Init() == -1)
		return;

	SDL_Color color = { 180, 180, 180, 255 };
	TTF_Font* large_font = TTF_OpenFont("./PTSansNarrow-Bold.ttf", 32);
	TTF_Font* small_font = TTF_OpenFont("./PTSansNarrow-Bold.ttf", 24);

	SDL_Texture* title_texture = render_text("A* SIMULATION TOOL", large_font, color);
	SDL_Texture* instructions_texture = render_text("0 - erase  |  1 - draw wall  |  2 - set start  |  3 - set end  |  ENTER - run  |  ESC - quit", small_font, color);
	SDL_Texture* prompt_texture = render_text("Press Enter to continue...", small_font, color);

	int w, h;

	SDL_QueryTexture(title_texture, NULL, NULL, &w, &h);
	SDL_Rect titleRect = { (this->width - w) / 2, 50, w, h };
	SDL_RenderCopy(renderer, title_texture, NULL, &titleRect);

	SDL_QueryTexture(instructions_texture, NULL, NULL, &w, &h);
	SDL_Rect instructionsRect = { (this->width - w) / 2, 150, w, h };
	SDL_RenderCopy(renderer, instructions_texture, NULL, &instructionsRect);

	SDL_QueryTexture(prompt_texture, NULL, NULL, &w, &h);
	SDL_Rect promptRect = { (this->width - w) / 2, 250, w, h };
	SDL_RenderCopy(renderer, prompt_texture, NULL, &promptRect);

	SDL_RenderPresent(renderer);

	bool over = false;

	while (!over)
	{
		SDL_Event event{ };

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
				over = true;
		}
	}

	SDL_RenderClear(renderer);

	SDL_DestroyTexture(title_texture);
	SDL_DestroyTexture(instructions_texture);
	SDL_DestroyTexture(prompt_texture);

	TTF_CloseFont(small_font);
	TTF_CloseFont(large_font);
	TTF_Quit();
}


SDL_Texture* Screen::render_text(const std::string& message, TTF_Font* font, SDL_Color color) 
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
	if (surface == nullptr) 
		return nullptr;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	if (texture == nullptr)
		return nullptr;

	SDL_FreeSurface(surface);
	return texture;
}


void Screen::idle(Physical& physical, bool* over)
{
	bool start = false;
	this->set_square_size(physical);

	while (!start)
	{
		SDL_Event event{ };

		this->draw_grid_idle(physical);

		this->event_handler(&event, physical, &start, over);
	}
}


void Screen::event_handler(SDL_Event* event, Physical& physical, bool* start, bool* over)
{
	while (SDL_PollEvent(event))
	{
		if (event->type == SDL_MOUSEBUTTONDOWN)
		{
			this->handle_mouse(event, physical);
			continue;
		}
		
		if (event->type == SDL_KEYDOWN)
		{
			this->handle_keyboard(event, start, over);
		}
	}
}


void Screen::handle_mouse(SDL_Event *event, Physical& physical)
{
	int x = event->button.x;
	int y = event->button.y;

	this->extract_square_coords(&x, &y);

	switch (this->current_option)
	{
	case PUT_EMPTY:
		physical.set_empty({ x, y });
		break;

	case PUT_WALL:
		physical.set_wall({ x, y });
		break;

	case PUT_START:
		physical.set_start({ x, y });
		break;

	case PUT_END:
		physical.set_end({ x, y });
		break;
	}
}


void Screen::handle_keyboard(SDL_Event* event, bool *start, bool* over)
{
	switch (event->key.keysym.sym)
	{
	case SDLK_0:
		this->current_option = PUT_EMPTY;
		break;

	case SDLK_1:
		this->current_option = PUT_WALL;
		break;

	case SDLK_2:
		this->current_option = PUT_START;
		break;

	case SDLK_3:
		this->current_option = PUT_END;
		break;

	case SDLK_RETURN:
		*start = true;
		break;

	case SDLK_ESCAPE:
		*over = true;
		*start = true;
		break;
	}
}


void Screen::extract_square_coords(int* x, int* y)
{
	*x = *x / this->rect_size_x;
	*y = *y / this->rect_size_y;
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
				this->set_color(BURGUNDY);
				break;
			}

			if (added[position.second][position.first])
			{
				this->set_color(BUFF);
				break;
			}

			this->set_color(WHITE);
			break;
	}
}


void Screen::draw_grid_idle(const Physical& physical)
{
	this->set_color(WHITE);

	SDL_Rect fillRect = { 0, 0, this->width, this->height };
	SDL_RenderFillRect(this->renderer, &fillRect);

	this->set_color(BLACK);
	for (int i = 0; i < physical.get_size_y(); i++)
	{
		for (int j = 0; j < physical.get_size_x(); j++)
		{
			SDL_Rect fill_rect = { j * this->rect_size_x, i * this->rect_size_y, this->rect_size_x, this->rect_size_y };
			if (physical.get_grid({ j, i }) == WALL)
				SDL_RenderFillRect(this->renderer, &fill_rect);

			/*else
				SDL_RenderDrawRect(this->renderer, &fill_rect);*/

		}
	}

	this->set_color(GREEN);
	SDL_Rect fill_rect_start = { physical.get_start().first * this->rect_size_x, physical.get_start().second * this->rect_size_y, this->rect_size_x, this->rect_size_y };
	SDL_RenderFillRect(this->renderer, &fill_rect_start);

	this->set_color(MAGENTA);
	SDL_Rect fill_rect_end = { physical.get_end().first * this->rect_size_x, physical.get_end().second * this->rect_size_y, this->rect_size_x, this->rect_size_y };
	SDL_RenderFillRect(this->renderer, &fill_rect_end);

	SDL_RenderPresent(this->renderer);
}


void Screen::draw_grid(const Physical& physical, std::unique_ptr<std::unique_ptr<bool[]>[]>& added,
	std::unique_ptr<std::unique_ptr<bool[]>[]>& visited)
{
	for (int i = 0; i < physical.get_size_y(); i++)
	{
		for (int j = 0; j < physical.get_size_x(); j++) 
		{
			this->set_alg_color({ j, i }, physical, added, visited);

			SDL_Rect fill_rect = { j * this->rect_size_x, i * this->rect_size_y, this->rect_size_x, this->rect_size_y };
			SDL_RenderFillRect(this->renderer, &fill_rect);

			/*this->set_color(BLACK);
			SDL_RenderDrawRect(this->renderer, &fill_rect);*/
		}
	}

	SDL_RenderPresent(this->renderer);

	SDL_Delay(5);
}


void Screen::draw_path(const Physical& physical, std::vector<std::pair<int, int>>& path)
{
	this->set_color(WHITE);

	SDL_Rect fill_rect = { 0, 0, this->width, this->height };
	SDL_RenderFillRect(this->renderer, &fill_rect);

	this->set_color(BLACK);
	for (int i = 0; i < physical.get_size_y(); i++)
	{
		for (int j = 0; j < physical.get_size_x(); j++)
		{
			SDL_Rect fill_rect = { j * this->rect_size_x, i * this->rect_size_y, this->rect_size_x, this->rect_size_y };
			if (physical.get_grid({ j, i }) == WALL)
				SDL_RenderFillRect(this->renderer, &fill_rect);

			/*else
				SDL_RenderDrawRect(this->renderer, &fill_rect);*/

		}
	}

	this->set_color(CARRIBEAN_CURRENT);
	for (int i = 0; i < path.size(); i++)
	{
		SDL_Rect fill_rect = { path[i].first * this->rect_size_x, path[i].second * this->rect_size_y, this->rect_size_x, this->rect_size_y };
		SDL_RenderFillRect(this->renderer, &fill_rect);
	}

	SDL_RenderPresent(this->renderer);

	SDL_Delay(5000);
}