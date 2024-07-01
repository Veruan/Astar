#include <stdio.h>

#include "Commander.h"
#include "Astar.h"
#include "Physical.h"

int main(int argc, char *argv[])
{	
	//Commander commander;
	Physical physical(10, 10);

	physical.set_end({ 4, 7 });
	physical.set_start({ 8, 4 });

	Astar(physical);

	return 0;
}