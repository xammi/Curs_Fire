#include "NS_Grid.h"
#include "time.h"

namespace Core {

//-------------------------------------------------------------------------------------------------
NS_Grid::NS_Grid(const int _N) :
    AbstractGrid(_N)
{
    uint T = time(NULL);
    qsrand(T);

    set_fields();
}

NS_Grid::~NS_Grid() {
    dispose_fields();
}

void NS_Grid::dispose_fields() {
    dealloc(u);
    dealloc(v);
    dealloc(dens);
    dealloc(u_src);
    dealloc(v_src);
    dealloc(dens_src);
}

void NS_Grid::set_fields() {
    u = alloc();
    v = alloc();
    dens = alloc();
    u_src = alloc();
    v_src = alloc();
    dens_src = alloc();
}

Field NS_Grid::alloc() const {
    Field result = new FVal * [N + 2];
    if (! result)
        throw MemNotAlloc();

    int N_1 = N + 1;
    for (int I = 0; I <= N_1; ++I) {
        result[I] = new FVal[N + 2];

        if (! result[I])
            throw MemNotAlloc();
    }
    return result;
}

void NS_Grid::dealloc(Field field) {
    if (! field) return;

    int N_1 = N + 1;
    for (int I = 0; I <= N_1; ++I)
        if (field[I])
            delete [] field[I];

    delete [] field;
}

float NS_Grid::density(int i, int j) const {
    return dens[i][j];
}

float NS_Grid::min_dens() const {
    return get_min(N, dens);
}

float NS_Grid::max_dens() const {
    return get_max(N, dens);
}

void NS_Grid::fill_random(Field field, FVal from, FVal to) {
    FVal factor = to - from;
    int I, J;

    for (I = 1; I <= N; I++)
        for (J = 1; J <= N; J++) {
            FVal num = qrand();
            field[I][J] =  num / RAND_MAX * factor + from;
        }
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

} // namespace Core
