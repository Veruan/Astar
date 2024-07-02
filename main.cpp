#include <stdio.h>

#include "Commander.h"
#include "Astar.h"
#include "Physical.h"

int main(int argc, char *argv[])
{	
	//Commander commander;
	Physical physical(5, 5);

	physical.set_start({ 1, 1 });
	physical.set_end({ 4, 3 });

	physical.set_wall_vertical(3, 1, 3);
	//physical.set_wall_horizontal(2, 1, 3);

	Astar(physical);

	return 0;
}