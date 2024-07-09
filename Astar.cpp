#include <cmath>

#include "AStar.h"
#include "utility.h"

void Astar(Commander& commander)
{
	bool path_exists;

	std::vector<std::shared_ptr<Node>> used;
	std::vector<std::pair<int, int>> path;

	{
		auto visited = allocate_2d_array(commander.get_physical().get_size_x(), commander.get_physical().get_size_y());
		auto added = allocate_2d_array(commander.get_physical().get_size_x(), commander.get_physical().get_size_y());
		std::unordered_map<std::pair<int, int>, std::weak_ptr<Node>, pair_hash> added_map;

		std::unique_ptr<Heap> priority_queue = std::make_unique<Heap>();

		priority_queue->insert(commander.get_physical().get_start(), nullptr, 0, 0);
	
		while (!priority_queue->empty())
		{
			auto current = priority_queue->extract_min();
			std::pair<int, int> position = current->get_position();

			used.push_back(current);
			visited[position.second][position.first] = true;

			if (commander.get_physical().get_grid(position) == END)
				break;
		
			get_neighbors(current, priority_queue, visited, added, added_map, commander.get_physical());

			commander.modify_screen().draw_grid(commander.get_physical(), added, visited);
		}

		path_exists = !priority_queue->empty();
		added_map.clear();
	}
	
	if(path_exists)
		reconstruct_path(used, path);

	commander.modify_screen().draw_path(commander.get_physical(), path);

	used.clear();
	path.clear();
}


void get_neighbors(std::shared_ptr<Node> current, std::unique_ptr<Heap>& priotirty_queue, std::unique_ptr<std::unique_ptr<bool[]>[]>& visited,
	std::unique_ptr<std::unique_ptr<bool[]>[]>& added, std::unordered_map<std::pair<int, int>, std::weak_ptr<Node>, pair_hash>& added_map, const Physical& physical)
{
	std::pair<int, int> position = current->get_position();
	
	// check for left, top, bottom, right distance 1 (times 10 for easier comparison)
	// check for corners (bigger distance sqrt(2) times 10 for easier comparison)

	for (int i = 0; i < 8; i++)
	{
		std::pair<int, int> new_position = { position.first + x_offset[i], position.second + y_offset[i] };

		if (!check_bounds(new_position, physical) || visited[new_position.second][new_position.first])
			continue;

		if (added[new_position.second][new_position.first])
		{
			update_node(current, new_position, added_map, priotirty_queue, i / 4);
			continue;
		}

		if(physical.get_grid(new_position) != WALL)
		{
			std::shared_ptr<Node> neighbor = std::make_shared<Node>(new_position, current, current->get_gcost() + costs[i / 4],
				hcost(new_position, physical.get_end()));

			priotirty_queue->insert(neighbor);

			added[new_position.second][new_position.first] = true;
			added_map[new_position] = neighbor;

			neighbor = nullptr;
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


void update_node(const std::shared_ptr<Node>& current, std::pair<int, int>& new_position, 
	std::unordered_map<std::pair<int, int>, std::weak_ptr<Node>, pair_hash>& added_map, std::unique_ptr<Heap>& priority_queue, const int cost_index)
{
	std::shared_ptr<Node> existing_node = added_map.at(new_position).lock();
	double new_gcost = current->get_gcost() + costs[cost_index];

	if (new_gcost < existing_node->get_gcost())
		priority_queue->decrease_key(priority_queue->get_heap_index(existing_node), new_gcost, current);

	existing_node = nullptr;
}


double hcost(const std::pair<int, int>& position, const std::pair<int, int>& end)
{
	int dx = abs(position.first - end.first);
	int dy = abs(position.second - end.second);
	return 10 * (dx + dy) + (14 - 2 * 10) * fmin(dx, dy);
}


void reconstruct_path(std::vector<std::shared_ptr<Node>>& used, std::vector<std::pair<int, int>>& path)
{
	std::shared_ptr<Node> current = used.back();
	while (true)
	{
		path.push_back(current->get_position());

		// start reached
		if (current->get_parent() == nullptr)
			break;

		current = current->get_parent();
	}
}


Node::Node(const std::pair<int, int>& position, std::shared_ptr<Node> parent, double gcost, double hcost) : position(position),
	parent(parent), gcost(gcost), hcost(hcost), fcost(hcost + gcost)
{}


Node::~Node()
{}


const std::pair<int, int>& Node::get_position() const
{
	return this->position;
}


std::shared_ptr<Node> Node::get_parent() const
{
	return this->parent;
}


double Node::get_gcost() const
{
	return this->gcost;
}


double Node::get_hcost() const
{
	return this->hcost;
}


double Node::get_fcost() const
{
	return this->fcost;
}


void Node::set_gcost(const double gcost)
{
	this->gcost = gcost;
}


void Node::set_hcost(const double hcost)
{
	this->hcost = hcost;
}


void Node::update_fcost()
{
	this->fcost = this->gcost + this->hcost;
}


void Node::update_parent(std::shared_ptr<Node> parent)
{
	this->parent = parent;
}


Heap::Heap() : size(0)
{}


Heap::~Heap()
{
	this->elements.clear();
	this->position_to_index.clear();
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


void Heap::heapify_down(const int index)
{
	// if heap has 0 or 1 elements, skip -> no nodes to check
	if (this->size <= 1)
		return;

    bool left = false, right = false;
    this->check_bounds(left, right, index);

	if (!left && !right)
		return;

    int left_index = (2 * index) + 1;
    int right_index = (2 * index) + 2;

    int smallest = index;

	// technically u dont need to check for left cuz if it didnt return left exists but for clarity reasons
    if (left && this->elements[left_index]->get_fcost() < this->elements[smallest]->get_fcost())
        smallest = left_index;

    if (right && this->elements[right_index]->get_fcost() < this->elements[smallest]->get_fcost())
        smallest = right_index;

    if (smallest != index) 
	{
		this->swap_position_to_index_values(index, smallest);
        std::swap(this->elements[index], this->elements[smallest]);

        heapify_down(smallest);
    }
}


void Heap::heapify_up(const int index)
{
	// if root or heap has 0 or 1 elements, skip -> no parents to check/no nodes to check
	if (this->size <= 1 || index == 0)
		return;

	int parent_index = (index - 1) / 2;

	if (this->elements[parent_index]->get_fcost() > this->elements[index]->get_fcost())
	{
		this->swap_position_to_index_values(parent_index, index);
		std::swap(this->elements[parent_index], this->elements[index]);

		heapify_up(parent_index);
	}
}


void Heap::insert(const std::pair<int, int>& position, std::shared_ptr<Node> parent, const double gcost, const double fcost)
{
	std::shared_ptr<Node> element = std::make_shared<Node>(position, parent, gcost, fcost);

	this->elements.push_back(element);
	this->size++;

	this->position_to_index[position] = this->size - 1;

	this->heapify_up(this->size - 1);
}


void Heap::insert(std::shared_ptr<Node> node)
{
	this->elements.push_back(node);
	this->size++;

	this->position_to_index[node->get_position()] = this->size - 1;

	this->heapify_up(this->size - 1);
}


std::shared_ptr<Node> Heap::extract_min() 
{
	if (this->size == 0)
		return nullptr;

	std::shared_ptr<Node> smallest = this->elements[0];
	this->position_to_index.erase(smallest->get_position());

	if (this->size > 1) 
	{
		this->elements[0] = this->elements.back();
		this->position_to_index.at(this->elements[0]->get_position()) = 0;
	}

	this->elements.pop_back();
	this->size--;

	this->heapify_down(0);

	return smallest;
}


void Heap::decrease_key(const int index, const double gcost, std::shared_ptr<Node> new_parent)
{
	this->elements[index]->set_gcost(gcost);
	this->elements[index]->update_fcost();
	this->elements[index]->update_parent(new_parent);

	this->heapify_up(index);
}


int Heap::get_heap_index(std::shared_ptr<Node> node)
{
	return this->position_to_index.at(node->get_position());
}


void Heap::swap_position_to_index_values(const int parent_index, const int child_index)
{
	this->position_to_index.at(this->elements[parent_index]->get_position()) = child_index;
	this->position_to_index.at(this->elements[child_index]->get_position()) = parent_index;
}