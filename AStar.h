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

struct pair_hash 
{
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2>& pair) const 
	{
		return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
	}
};


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

		std::unordered_map<std::pair<int, int>, int, pair_hash> position_to_index;

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

		void decrease_key(const int index, const double gcost, std::shared_ptr<Node> new_parent);

		int get_heap_index(std::shared_ptr<Node> node);

		void swap_position_to_index_values(const int parent_index, const int child_index);
};



void Astar(Commander& commander);


void get_neighbors(std::shared_ptr<Node> current, std::unique_ptr<Heap>& priotirty_queue, std::unique_ptr<std::unique_ptr<bool[]>[]>& visited,
	std::unique_ptr<std::unique_ptr<bool[]>[]>& added, std::unordered_map<std::pair<int, int>, std::weak_ptr<Node>, pair_hash>& added_map, const Physical& physical);

bool check_bounds(std::pair<int, int>& position, const Physical& physical);

void update_node(const std::shared_ptr<Node>& current, std::pair<int, int>& new_position,
	std::unordered_map<std::pair<int, int>, std::weak_ptr<Node>, pair_hash>& added_map, std::unique_ptr<Heap>& priority_queue, const int cost_index);


double hcost(const std::pair<int, int>& position, const std::pair<int, int>& end);


void reconstruct_path(std::vector<std::shared_ptr<Node>>& used, std::vector<std::pair<int, int>>& path);

#endif