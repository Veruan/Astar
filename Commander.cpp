#include "Commander.h"


// should be stack allocated 
Commander::Commander() : screen(1080, 720), physical(40, 40)
{}


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