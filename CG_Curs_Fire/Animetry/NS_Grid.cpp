#include "NS_Grid.h"
#include "time.h"

namespace Core {

//-------------------------------------------------------------------------------------------------
NS_Grid::NS_Grid(const int _N) :
    AbstractGrid(_N)
{
    uint T = time(NULL);
    qsrand(T);

    set_conf();
}

NS_Grid::~NS_Grid() {
    dispose_conf();
}

void NS_Grid::dispose_conf() {
    if (u) delete [] u;
    if (v) delete [] v;
    if (dens) delete [] dens;

    if (u_src) delete [] u_src;
    if (v_src) delete [] v_src;
    if (dens_src) delete [] dens_src;
}

void NS_Grid::set_conf() {
    u = new float[size];
    v = new float[size];
    dens = new float[size];

    u_src = new float[size];
    v_src = new float[size];
    dens_src = new float[size];

    if (!u || !v || !dens || !u_src || !v_src || !dens_src)
        throw MemNotAlloc();

    to_zero(size, u);
    to_zero(size, v);
    to_zero(size, dens);
    to_zero(size, u_src);
    to_zero(size, v_src);
    to_zero(size, dens_src);
}

float NS_Grid::density(int i, int j) const {
    return dens[IX(i, j)];
}

float NS_Grid::min_dens() const {
    return get_min(size, dens);
}

float NS_Grid::max_dens() const {
    return get_max(size, dens);
}

void NS_Grid::fill_random(float * src, float from, float to) {
    float factor = to - from;

    for (int i = 0; i < size; i++) {
         float num = qrand();
         src[i] = num / RAND_MAX * factor + from;
    }
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

} // namespace Core
