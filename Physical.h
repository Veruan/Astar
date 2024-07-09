#ifndef ASTAR_PHYSICAL_H
#define ASTAR_PHYSICAL_H

#include <vector>

enum Fields
{
	END = '3',
	START = '2',
	WALL = '1',
	EMPTY = '0'
};


class Physical
{
	private:

		int size_x;
		int size_y;

		std::vector<std::vector<char>> grid;

		std::pair<int, int> start;
		std::pair<int, int> end;
		// {x , y}

	public:

		Physical(int size_x, int size_y);

		~Physical();

		void set_start(const std::pair<int, int>& position);

		void set_end(const std::pair<int, int>& position);

		void set_wall(const std::pair<int, int>& position);

		void set_empty(const std::pair<int, int>& position);

		void set_wall_horizontal(int row, int start, int end);
		
		void set_wall_vertical(int col, int start, int end);

		char get_grid(const std::pair<int, int>& position) const;

		std::pair<int, int> get_start() const;

		std::pair<int, int> get_end() const;

		int get_size_x() const;

		int get_size_y() const;
};

#endif