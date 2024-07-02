#include <stdio.h>

#include "Commander.h"
#include "Astar.h"
#include "Physical.h"

int main(int argc, char *argv[])
{	
	//Commander commander;
	Physical physical(40, 40);

	physical.set_start({ 1, 1 });
	physical.set_end({ 38, 27 });

	physical.set_wall_vertical(3, 1, 30);
	//physical.set_wall_horizontal(2, 1, 3);

	Astar(physical);

	return 0;
}