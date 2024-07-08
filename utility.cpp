#include "utility.h"

std::unique_ptr<std::unique_ptr<bool[]>[]> allocate_2d_array(int size_x, int size_y)
{
    std::unique_ptr<std::unique_ptr<bool[]>[]> arr(new std::unique_ptr<bool[]>[size_y]);
    for (int i = 0; i < size_y; i++)
    {
        arr[i] = std::make_unique<bool[]>(size_x);
        for (int j = 0; j < size_x; j++)
        {
            arr[i][j] = false;
        }
    }
    return arr;
}
