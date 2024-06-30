#ifndef ASTAR_ASTAR_H
#define ASTAR_ASTAR_H

#include <vector>
#include <memory>

#include "Physical.h"

const std::pair<int, int> start_parent = { -2, -2 };

void Astar(const Physical& physical);

double fcost(const std::pair<int, int>& position, const std::pair<int, int>& start, const std::pair<int, int>& end);

double gcost(const std::pair<int, int>& position, const std::pair<int, int>& start);
double hcost(const std::pair<int, int>& position, const std::pair<int, int>& end);


class Node
{
	private:

		const std::pair<int, int> position;
		const std::pair<int, int> parent;

		const double cost;

	public:

		Node(const std::pair<int, int>& position, const std::pair<int, int>& parent, const double cost);

		~Node();

		const std::pair<int, int>& get_position();

		const std::pair<int, int>& get_parent();

		double get_cost() const;
};


class Heap
{
	private:

		int size;
		std::vector<Node *> elements;

	public:

		Heap();

		~Heap();

		bool empty();

		void check_bounds(bool& left, bool& right, int index) const;

		void heapify_down(int index);

		void heapify_up(int index);

		void insert(const std::pair<int, int>& position, const std::pair<int, int>& parent, const double cost);

		Node* extract_min();
};

#endif