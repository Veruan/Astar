#ifndef ASTAR_ASTAR_H
#define ASTAR_ASTAR_H

#include <vector>
#include <unordered_map>
#include <memory>

#include "Commander.h"

// left, top, bottom, right, top-left, bottom-left, top-right, bottom-right
const int x_offset[] = {-1, 0, 0, 1, -1, -1, 1, 1};
const int y_offset[] = {0, -1, 1, 0, -1, 1, -1, 1};

const int costs[] = { 10, 14 };

class Node
{
	private:

		const std::pair<int, int> position;
		std::shared_ptr<Node> parent;

		double gcost;
		double hcost;
		double fcost;

	public:

		Node(const std::pair<int, int>& position, std::shared_ptr<Node> parent, double gcost, double hcost);

		~Node();

		const std::pair<int, int>& get_position() const;

		std::shared_ptr<Node> get_parent() const;

		double get_gcost() const;

		double get_hcost() const;

		double get_fcost() const;

		void set_gcost(const double gcost);

		void set_hcost(const double hcost);

		void update_fcost();

		void update_parent(std::shared_ptr<Node> parent);
};


class Heap
{
	private:

		int size;
		std::vector<std::shared_ptr<Node>> elements;

	public:

		Heap();

		~Heap();

		bool empty();

		void check_bounds(bool& left, bool& right, int index) const;

		void heapify_down(const int index);

		void heapify_up(const int index);

		void insert(const std::pair<int, int>& position, std::shared_ptr<Node> parent, const double gcost, const double hcost);

		void insert(std::shared_ptr<Node> node);

		std::shared_ptr<Node> extract_min();

		void decrease_key(const int index, const double gcost);
};



void Astar(Commander& commander);


void get_neighbors(std::shared_ptr<Node> current, std::unique_ptr<Heap>& priotirty_queue, std::unique_ptr<std::unique_ptr<bool[]>[]>& visited,
	std::unique_ptr<std::unique_ptr<bool[]>[]>& added, const Physical& physical);

bool check_bounds(std::pair<int, int>& position, const Physical& physical);


double hcost(const std::pair<int, int>& position, const std::pair<int, int>& end);


void reconstruct_path(std::vector<std::shared_ptr<Node>>& used, std::vector<std::pair<int, int>>& path);

#endif


/*
added_map = std::unordered_map<std::pair<int, int>, std::weak_ptr<Node>>;

if (added[new_position.second][new_position.first])
		{
			added_map.at(new_position).lock();
			double new_cost = current->get_cost();

			if (new_cost > added_map.at(new_position).get_cost())
			{
				added_map.at(new_position).set_gcost(current->get_gcost());
				added_map.at(new_position).update_fcost();
				added_map.at(new_position).update_parent(current);
				// update heap?
				// unlock
			}
		}
*/