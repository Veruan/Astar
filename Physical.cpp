#include "Physical.h"

Physical::Physical(int size_x, int size_y) : size_x(size_x), size_y(size_y), start({0, 0}), end({size_x - 1, size_y - 1})
{
	this->grid.resize(size_y, std::vector<char>(size_x));

	for (auto& row : this->grid)
	{
		row.assign(size_x, EMPTY);
	}

	this->grid[start.second][start.first] = START;
	this->grid[end.second][end.first] = END;
}


Physical::~Physical()
{
	this->grid.clear();
}


void Physical::set_start(const std::pair<int, int>& position)
{
	this->grid[this->start.second][this->start.first] = EMPTY;

	this->start = position;
	this->grid[position.second][position.first] = START;
}


void Physical::set_end(const std::pair<int, int>& position)
{
	this->grid[this->end.second][this->end.first] = EMPTY;

	this->end = position;
	this->grid[position.second][position.first] = END;
}


void Physical::set_wall(const std::pair<int, int>& position)
{
	this->grid[position.second][position.first] = WALL;
}


void Physical::set_empty(const std::pair<int, int>& position)
{
	this->grid[position.second][position.first] = EMPTY;
}


void Physical::set_wall_horizontal(int row, int start, int end)
{
	for (int i = start; i <= end; i++)
		this->grid[row][i] = WALL;
}


void Physical::set_wall_vertical(int col, int start, int end)
{
	for (int i = start; i <= end; i++)
		this->grid[i][col] = WALL;
}


char Physical::get_grid(const std::pair<int, int>& position) const
{
	return this->grid[position.second][position.first];
}


std::pair<int, int> Physical::get_start() const
{
	return this->start;
}


std::pair<int, int> Physical::get_end() const
{
	return this->end;
}


int Physical::get_size_x() const
{
	return this->size_x;
}


int Physical::get_size_y() const
{
	return this->size_y;
}