#include "Commander.h"
#include "Astar.h"
#include "Physical.h"

int main(int argc, char *argv[])
{	
	bool over = false;
	Commander commander;

	commander.modify_screen().menu();
	while (true)
	{
		commander.modify_screen().idle(commander.modify_physical(), &over);
		if (over)
			break;

		Astar(commander);
	}

	return 0;
}