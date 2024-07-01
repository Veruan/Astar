#include <cmath>

#include "AStar.h"
#include "utility.h"

void Astar(const Physical& physical)
{
	std::vector<Node*> used;
	std::vector<Node*> path;

	{
		bool **visited = allocate_2d_array(physical.get_size_x(), physical.get_size_y());
		bool **added = allocate_2d_array(physical.get_size_x(), physical.get_size_y());

		std::unique_ptr<Heap> priority_queue = std::make_unique<Heap>();
		std::vector<Node*> neighbors;

		priority_queue->insert(physical.get_start(), nullptr, 0);
	
		while (!priority_queue->empty())
		{
			Node* current = priority_queue->extract_min();
			std::pair<int, int> position = current->get_position();

			used.push_back(current);
			visited[position.second][position.first] = true;

			if (physical.get_grid(position) == END)
				break;
		
			get_neighbors(current, neighbors, visited, added, physical);
			for(Node* node : neighbors)
			{
				node->add_cost(hcost(node->get_position(), physical.get_end()));
				priority_queue->insert(node);
			}

			neighbors.clear();
		}

		delete_2d_array(physical.get_size_x(), physical.get_size_y(), &visited);
		delete_2d_array(physical.get_size_x(), physical.get_size_y(), &added);
	}
	
	reconstruct_path(used, path);

	for (int i = path.size() - 1; i >= 0; i--)
		std::cout << path[i]->get_position().first << ", " << path[i]->get_position().second << '\n';

	for (Node* element : used)
		delete element;

	used.clear();
	path.clear();
}


void get_neighbors(Node* current, std::vector<Node*>& neighbors, bool** visited, bool** added, const Physical& physical)
{
	std::pair<int, int> position = current->get_position();

	for (int i = 0; i < 4; i++)
	{
		std::pair<int, int> new_position = { position.first + x_offset[i], position.second + y_offset[i] };

		if(check_bounds(new_position, physical) && !visited[new_position.second][new_position.first] && !added[new_position.second][new_position.first])
		{
			Node* neighbor = new Node(new_position, current, current->get_cost() + 10);
			neighbors.push_back(neighbor);

			added[new_position.second][new_position.first] = true;
		}
	}

	for (int i = 4; i < 8; i++)
	{
		std::pair<int, int> new_position = { position.first + x_offset[i], position.second + y_offset[i] };

		if (check_bounds(new_position, physical) && !visited[new_position.second][new_position.first] && !added[new_position.second][new_position.first])
		{
			Node* neighbor = new Node(new_position, current, current->get_cost() + 14);
			neighbors.push_back(neighbor);

			added[new_position.second][new_position.first] = true;
		}
	}
}


bool check_bounds(std::pair<int, int>&position, const Physical& physical)
{
	bool x = false, y = false;

	x = (position.first >= 0 && position.first <= physical.get_size_x() - 1);
	y = (position.second >= 0 && position.second <= physical.get_size_y() - 1);

	return (x && y);
}


double hcost(const std::pair<int, int>& position, const std::pair<int, int>& end)
{
	return sqrt(pow(end.first - position.first, 2) + pow(end.second - position.second, 2));
}


void reconstruct_path(std::vector<Node*>& used, std::vector<Node*>& path)
{
	Node* current = used[used.size() - 1];
	while (true)
	{
		path.push_back(current);

		// start reached
		if (current->get_parent() == nullptr)
			break;

		current = current->get_parent();
	}
}


Node::Node(const std::pair<int, int>& position, Node *parent, double gcost) : position(position), parent(parent), cost(gcost)
{}


Node::~Node()
{}


void Node::add_cost(double hcost)
{
	this->cost += hcost;
}


const std::pair<int, int>& Node::get_position() const
{
	return this->position;
}


Node* Node::get_parent() const
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


void Heap::insert(const std::pair<int, int>& position, Node *parent, const double cost)
{
	Node* element = new Node(position, parent, cost);

	this->elements.push_back(element);
	this->size++;

	this->heapify_up(this->size - 1);
}


void Heap::insert(Node* node)
{
	this->elements.push_back(node);
	this->size++;

	this->heapify_up(this->size - 1);
}


Node* Heap::extract_min()
{
	if (this->size == 0)
		return nullptr;

	Node *smallest = this->elements[0];

	this->elements[0] = this->elements[this->size - 1];

	this->elements.pop_back();
	this->size--;

	this->heapify_down(0);

	return smallest;
}