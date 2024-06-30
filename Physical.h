#ifndef ASTAR_PHYSICAL_H
#define ASTAR_PHYSICAL_H

#include <vector>

class Physical
{
	private:

		int size_x;
		int size_y;

		std::vector<std::vector<bool>> grid;

		std::pair<int, int> start;
		std::pair<int, int> end;
		// {x , y}

	public:

		Physical(int size_x, int size_y);

		~Physical();
};

#endif