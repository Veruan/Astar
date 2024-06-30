#include "Physical.h"

Physical::Physical(int size_x, int size_y) : size_x(size_x), size_y(size_y), start({0, 0}), end({size_x - 1, size_y - 1})
{
	this->grid.resize(size_y, std::vector<bool>(size_x));

	for (auto& row : this->grid)
	{
		row.assign(size_x, false);
	}
}


Physical::~Physical()
{

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