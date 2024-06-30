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