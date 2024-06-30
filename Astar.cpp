#include "AStar.h"

void Astar(const Physical& physical)
{
	Heap priority_queue;
	std::vector<Node*> used;

	bool** visited = new bool* [physical.get_size_y()];
		for (int i = 0; i < physical.get_size_y(); i++)
			visited[i] = new bool [physical.get_size_x()];

	priority_queue.insert(physical.get_start(), start_parent, 0);
	
	while (!priority_queue.empty())
	{
		Node* current = priority_queue.extract_min();
		std::pair<int, int> position = current->get_position();

		used.push_back(current);
		visited[position.second][position.first] = true;

		if (current->get_position() == physical.get_end())
			break;
		
		for (int i = 0; i < 8; i++)
		{
			if (visited[position.second][position.first])
				continue;

			// calculate cost
			// priority_queue.insert(position, current.get_position(), cost);
		}
	}

	for (int i = 0; i < physical.get_size_y(); i++)
		delete[] visited[i];
	delete[] visited;

	//reconstruct_path;

	for (Node* element : used)
		delete element;

	used.clear();
}


double fcost(const std::pair<int, int>& position, const std::pair<int, int>& start, const std::pair<int, int>& end)
{
	return 0;
}


double gcost(const std::pair<int, int>& position, const std::pair<int, int>& start)
{
	return 0;
}


double hcost(const std::pair<int, int>& position, const std::pair<int, int>& end)
{
	return 0;
}


Node::Node(const std::pair<int, int>& position, const std::pair<int, int>& parent, const double cost) : position(position), parent(parent), cost(cost)
{}


Node::~Node()
{}


const std::pair<int, int>& Node::get_position()
{
	return this->position;
}


const std::pair<int, int>& Node::get_parent()
{
	return this->parent;
}


double Node::get_cost() const
{
	return this->cost;
}


Heap::Heap() : size(0)
{}


Heap::~Heap()
{
	for (Node* element : this->elements)
		delete element;

	this->elements.clear();
}


bool Heap::empty()
{
	if (this->size == 0)
		return true;

	return false;
}


void Heap::check_bounds(bool& left, bool& right, int index) const
{
	// node is a leaf
	if (index >= this->size / 2)
		return;


	// left child is last element in the heap so no right child 
	if (2 * index  + 1 == this->size - 1)
	{
		left = true;
		return;
	}


	if (2 * index + 2 <= this->size - 1)
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

    int left_index = (2 * index) + 1;
    int right_index = (2 * index) + 2;

    int smallest = index;

	// technically u dont need to check for left cuz if it didnt return left exists but for clarity reasons
    if (left && this->elements[left_index]->get_cost() < this->elements[smallest]->get_cost())
        smallest = left_index;

    if (right && this->elements[right_index]->get_cost() < this->elements[smallest]->get_cost())
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

	int parent_index = (index - 1) / 2;

	if (this->elements[parent_index]->get_cost() > this->elements[index]->get_cost())
	{
		std::swap(this->elements[parent_index], this->elements[index]);
		heapify_up(parent_index);
	}
}


void Heap::insert(const std::pair<int, int>& position, const std::pair<int, int>& parent, const double cost)
{
	Node* element = new Node(position, parent, cost);

	this->elements.push_back(element);
	this->size++;

	this->heapify_up(this->size - 1);
}


Node* Heap::extract_min()
{
	if (this->size == 0)
		return nullptr;

	Node *smallest = this->elements[this->size - 1];

	this->elements[0] = this->elements[this->size - 1];

	this->elements.pop_back();
	this->size--;

	this->heapify_down(0);

	return smallest;
}

//priority Q


//heuristic function


//Astar