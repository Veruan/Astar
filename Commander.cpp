#include "Commander.h"


// should be stack allocated 
Commander::Commander() : screen(1080, 720), physical(40, 40)
{
	this->modify_physical().set_start({ 1, 1 });
	this->modify_physical().set_end({ 15, 25 });

	this->modify_physical().set_wall_vertical(5, 5, 15);
	this->modify_physical().set_wall_horizontal(10, 5, 15);
	this->modify_physical().set_wall_vertical(15, 10, 20);
	this->modify_physical().set_wall_horizontal(20, 10, 20);

	this->modify_physical().set_wall_vertical(25, 25, 35);
	this->modify_physical().set_wall_horizontal(30, 25, 35);
	this->modify_physical().set_wall_vertical(35, 30, 39);
	this->modify_physical().set_wall_horizontal(39, 30, 39);

	this->modify_physical().set_wall_vertical(10, 20, 30);
	this->modify_physical().set_wall_horizontal(15, 20, 30);
	this->modify_physical().set_wall_vertical(20, 25, 35);
	this->modify_physical().set_wall_horizontal(25, 25, 35);
}


Commander::~Commander()
{}


const Physical& Commander::get_physical() const
{
	return this->physical;
}


Physical& Commander::modify_physical()
{
	return this->physical;
}


const Screen& Commander::get_screen() const
{
	return this->screen;
}


Screen& Commander::modify_screen()
{
	return this->screen;
}