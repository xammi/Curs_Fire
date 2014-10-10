#ifndef AGRID_H
#define AGRID_H

#include "../includes.h"

#define GEN_N 40

typedef float FVal;
typedef FVal ** Field;

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
void print_debug(int N, T ** array) {
    int N_1 = N + 1;
    for (int I = 0; I <= N_1; I++) {
        for (int J = 0; J <= N_1; J++)
            qDebug("  %4.2f", array[I][J]);
        qDebug("\n");
    }
}

template <typename T>
T get_min(int N, T ** array) {
    int N_1 = N + 1;
    T min = array[0][0];

    for (int I = 0; I <= N_1; I++)
        for (int J = 0; J <= N_1; J++)
            if (min > array[I][J])
                min = array[I][J];

    return min;
}

template <typename T>
T get_max(int N, T ** array) {
    T max = array[0][0];
    int N_1 = N + 1;

    for (int I = 0; I <= N_1; I++)
        for (int J = 0; J <= N_1; J++)
            if (max < array[I][J])
                max = array[I][J];

    return max;
}

struct MemNotAlloc : public Exception {
    QString to_string() { return "Memory for grid was not allocated"; }
};

} // namespace Core

#endif // AGRID_H
