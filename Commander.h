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

		const Physical& get_physical() const;

		Physical& modify_physical();

		const Screen& get_screen() const;

		Screen& modify_screen();
};

#endif