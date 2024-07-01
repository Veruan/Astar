#ifndef ASTAR_ASTAR_H
#define ASTAR_ASTAR_H

#include <iostream>
#include <vector>
#include <memory>

#include "Physical.h"

const char END = '3';

// left, top, bottom, right, top-left, bottom-left, top-right, bottom-right
const int x_offset[] = {-1, 0, 0, 1, -1, -1, 1, 1};
const int y_offset[] = {0, -1, 1, 0, -1, 1, -1, 1};


class Node
{
	private:

		const std::pair<int, int> position;
		Node *parent;

		double cost;

	public:

		Node(const std::pair<int, int>& position, Node* parent, double cost);

		~Node();

		void add_cost(double hcost);

		const std::pair<int, int>& get_position() const;

		Node* get_parent() const;

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

		void insert(const std::pair<int, int>& position, Node* parent, const double cost);

		void insert(Node* node);

		Node* extract_min();
};



void Astar(const Physical& physical);



void get_neighbors(Node* current, std::vector<Node*>& neighbors, bool** visited, const Physical& physical);
bool check_bounds(std::pair<int, int>& position, const Physical& physical);


double hcost(const std::pair<int, int>& position, const std::pair<int, int>& end);


void reconstruct_path(std::vector<Node*>& used, std::vector<Node*>& path);

#endif