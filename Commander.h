#ifndef ASTAR_COMMANDER_H
#define ASTAR_COMMANDER_H

#include <memory>

#include "Screen.h"
#include "Physical.h"


class Commander
{
	private:

		Screen screen;
		Physical physical;

	public:

		Commander();

		~Commander();
		
};

#endif