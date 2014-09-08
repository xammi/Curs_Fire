#include "agrid.h"

namespace Core {
//-------------------------------------------------------------------------------------------------

AbstractGrid::AbstractGrid()
{
}

//-------------------------------------------------------------------------------------------------
void assign(int size, float * src, float * array) {
    for (int i = 0; i < size; i++)
        array[i] = src[i];
}

float get_min(int size, float * array) {
    float min = array[0];
    for (int i = 1; i < size; i++)
        if (min > array[i])
            min = array[i];

    return min;
}

float get_max(int size, float * array) {
    float max = array[0];
    for (int i = 1; i < size; i++)
        if (max < array[i])
            max = array[i];

    return max;
}

void fill_random(int size, float * src, float from, float to) {
    float factor = to - from;

    for (int i = 0; i < size; i++) {
         float num = qrand();
         src[i] = num / RAND_MAX * factor + from;
    }
}
//-------------------------------------------------------------------------------------------------
} // namespace Core
