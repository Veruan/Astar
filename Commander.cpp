#include "Commander.h"

Commander::Commander()
{
	this->screen = std::make_shared<Screen>();

	this->physical = std::make_shared<Physical>(10, 10);
}

Commander::~Commander()
{

}