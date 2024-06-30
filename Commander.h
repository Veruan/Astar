#ifndef ASTAR_COMMANDER_H
#define ASTAR_COMMANDER_H

#include <shared_mutex>

#include "Screen.h"
#include "Physical.h"


class Commander
{
	private:

		std::shared_ptr<Screen> screen;
		std::shared_ptr<Physical> physical;

	public:

		Commander();

		~Commander();
		
};

#endif