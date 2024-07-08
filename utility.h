#ifndef BASIC_UTILITY_H
#define BASIC_UTILITY_H

#include <vector>
#include <memory>

std::unique_ptr<std::unique_ptr<bool[]>[]> allocate_2d_array(int size_x, int size_y);


#endif