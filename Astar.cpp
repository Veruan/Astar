#include "AStar.h"

void Astar(const std::pair<int, int>& start, const std::pair<int, int>& end, const std::vector<std::vector<bool>>& physical_layer)
{
	// Astar code
}


Node::Node()
{}

Node::~Node()
{}

const std::pair<int, int> Node::get_parent()
{}

void Node::calc_cost(const std::pair<int, int>& start, const std::pair<int, int>& end)
{
}

int Node::get_cost() const
{
	return this->cost;
}


Heap::Heap() : size(0)
{}


Heap::~Heap()
{
	this->elements.clear();
}


void Heap::check_bounds(bool& left, bool& right, int index)
{
	// node is a leaf
	if (index >= this->size / 2)
		return;


	// left child is last element in the heap so no right child 
	if (2 * index == this->size - 1)
	{
		left = true;
		return;
	}


	if (2 * index + 1 <= this->size - 1)
	{
		left = true;
		right = true;
		return;
	}

}


void Heap::heapify_down(int index) 
{
    bool left = false, right = false;
    this->check_bounds(left, right, index);

	if (!left && !right)
		return;

    int left_index = 2 * index + 1;
    int right_index = 2 * index + 2;

    int smallest = index;

	// technically u dont need to check for left cuz if it didnt return left exists but for clarity reasons
    if (left && this->elements[left_index].get_cost() < this->elements[smallest].get_cost())
        smallest = left_index;

    if (right && this->elements[right_index].get_cost() < this->elements[smallest].get_cost())
        smallest = right_index;

    if (smallest != index) 
	{
        std::swap(elements[index], elements[smallest]);
        heapify_down(smallest);
    }
}


void Heap::heapify_up(int index)
{
	if (index == 0)
		return;

	if (this->elements[(index - 1) / 2].get_cost() > this->elements[index].get_cost())
	{
		std::swap(elements[(index - 1) / 2], elements[index]);
		heapify_up((index - 1) / 2);
	}
}


void Heap::insert(const Node& element)
{
	this->elements.push_back(element);
	this->size++;

	this->heapify_up(this->size - 1);
}


Node& Heap::extract_min()
{
	Node smallest = std::move(this->elements[0]);

	this->elements[0] = this->elements[this->size - 1];
	this->elements.pop_back();
	this->size--;

	this->heapify_down(0);

	return smallest;
}

//priority Q


//heuristic function


//Astar