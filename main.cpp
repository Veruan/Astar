#include "Commander.h"
#include "Astar.h"
#include "Physical.h"

int main(int argc, char *argv[])
{	
	Commander commander;

	// Random
	commander.modify_physical().set_start({ 1, 1 });
	commander.modify_physical().set_end({15, 25});

	commander.modify_physical().set_wall_vertical(5, 5, 15);
	commander.modify_physical().set_wall_horizontal(10, 5, 15);
	commander.modify_physical().set_wall_vertical(15, 10, 20);
	commander.modify_physical().set_wall_horizontal(20, 10, 20);

	commander.modify_physical().set_wall_vertical(25, 25, 35);
	commander.modify_physical().set_wall_horizontal(30, 25, 35);
	commander.modify_physical().set_wall_vertical(35, 30, 39);
	commander.modify_physical().set_wall_horizontal(39, 30, 39);

	commander.modify_physical().set_wall_vertical(10, 20, 30);
	commander.modify_physical().set_wall_horizontal(15, 20, 30);
	commander.modify_physical().set_wall_vertical(20, 25, 35);
	commander.modify_physical().set_wall_horizontal(25, 25, 35);

	commander.modify_screen().idle(commander.modify_physical());
	Astar(commander);

	return 0;
}