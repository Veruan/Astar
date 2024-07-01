#include "utility.h"


bool** allocate_2d_array(int size_x, int size_y)
{
	bool** arr = new bool* [size_y];
	for (int i = 0; i < size_y; i++)
	{
		arr[i] = new bool[size_x];
		for (int j = 0; j < size_x; j++)
			arr[i][j] = false;
	}

	return arr;
}


void delete_2d_array(int size_x, int size_y, bool*** arr)
{
	for (int i = 0; i < size_y; i++)
		delete[] (*arr)[i];
	delete[] *arr;
}