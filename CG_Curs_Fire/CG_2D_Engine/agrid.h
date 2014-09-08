#ifndef AGRID_H
#define AGRID_H

#include "exception.h"
#include "tuple"

namespace Core {

//-------------------------------------------------------------------------------------------------
class AbstractGrid
{
public:
    AbstractGrid(const int);

    bool correct_N(int _N) const { return N == _N; }

protected:
    const int N;
    const int size;
};

//-------------------------------------------------------------------------------------------------
// engine utils
//-------------------------------------------------------------------------------------------------
template <typename T>
void to_zero(int size, T * array) {
    for (int i = 0; i < size; i++)
        array[i] = 0;
}

template <typename T>
void print_debug(int size, T * array) {
    for (int i = 0; i < size; i++)
        qDebug() << array[i];
}

template <typename T>
void assign(int size, T * src, T * array) {
    for (int i = 0; i < size; i++)
        array[i] = src[i];
}

template <typename T>
float get_min(int size, T * array) {
    T min = array[0];
    for (int i = 1; i < size; i++)
        if (min > array[i])
            min = array[i];

    return min;
}

template <typename T>
T get_max(int size, T * array) {
    T max = array[0];
    for (int i = 1; i < size; i++)
        if (max < array[i])
            max = array[i];

    return max;
}

struct MemNotAlloc : public Exception {
    QString to_string() { return "Memory for grid was not allocated"; }
};

} // namespace Core

#endif // AGRID_H
