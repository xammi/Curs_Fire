#include "ns_grid.h"
#include "time.h"

namespace Core {

//-------------------------------------------------------------------------------------------------
NS_Grid::NS_Grid(const int _N) :
    N(_N)
{
    size = (N+2) * (N+2);
    set_conf();
    set_src();
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
void NS_Grid::set_src() {
//    set_density_src();
//    set_velocity_src();

    uint T = time(NULL);
    qsrand(T);

    fill_random(size, u_src, -3, 3);
    fill_random(size, v_src, -3, 3);
    fill_random(size, dens_src, -1, 1);
}

void NS_Grid::set_density_src() {
    dens_src[IX(5,5)] = 1;
    dens_src[IX(15, 12)] = -0.5;
    dens_src[IX(22,34)] = 3;
    dens_src[IX(25,30)] = -1;
}

void NS_Grid::set_velocity_src() {
    u_src[IX(3,2)] = 0.1;
    u_src[IX(8,4)] = 0.1;
    v_src[IX(12,15)] = 0.2;
}
//-------------------------------------------------------------------------------------------------

} // namespace Core
