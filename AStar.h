#ifndef ASTAR_ASTAR_H
#define ASTAR_ASTAR_H

#include <vector>

void Astar(const std::pair<int, int>& start, const std::pair<int, int>& end, const std::vector<std::vector<bool>>& physical_layer);


class Node
{
	private:

		std::pair<int, int> position;

		int cost;

		std::pair<int, int> parent;

	public:

		Node();

		~Node();

		const std::pair<int, int> get_parent();

		void calc_cost(const std::pair<int, int>& start, const std::pair<int, int>& end);

		int get_cost() const;
};


class Heap
{
	private:

		size_t size;
		std::vector<Node> elements;

	public:

		Heap();

		~Heap();

		void check_bounds(bool& left, bool& right, int index);

		void heapify_down(int index);

		void heapify_up(int index);

		void insert(const Node&);

		Node& extract_min();
};

#endif