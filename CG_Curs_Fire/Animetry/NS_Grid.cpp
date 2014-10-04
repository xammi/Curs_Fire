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

void NS_Grid::fill_random(float * src, float from, float to) {
    float factor = to - from;

    for (int i = 0; i < size; i++) {
         float num = qrand();
         src[i] = num / RAND_MAX * factor + from;
    }
}
//-------------------------------------------------------------------------------------------------
void NS_Grid::set_src() {
    set_density_src();
    set_velocity_src();
//    set_random_src();
}

void NS_Grid::set_density_src() {
    float POSIT = 50;
    float NEGAT_SIDE = 0;
    float NEGAT_TOP = 0;

    for (int I = 10; I <= N - 10; I++)
        dens_src[IX(N, I)] = POSIT;

    for (int I = 1; I < N - 1; I++) {
        dens_src[IX(I, 1)] = NEGAT_SIDE;
        dens_src[IX(I, N)] = NEGAT_SIDE;
    }

    for (int I = 10; I <= N-10; I++)
        dens_src[IX(30, I)] = NEGAT_TOP;
}

void NS_Grid::set_velocity_src() {
    float UP = -10;

    for (int I = 1; I <= N; I++)
        for (int J = 1; J <= N; J++) {
            u_src[IX(I,J)] = UP;
        }
}

void NS_Grid::set_random_src() {
    fill_random(u_src, I2F(-5), I2F(5));
    fill_random(v_src, I2F(-5), I2F(5));
    fill_random(dens_src, I2F(-2), I2F(2));
}

void NS_Grid::fluctuations() {
    fill_random(u_src, I2F(-4), I2F(4));
//    fill_random(v_src, -0.1, 0.1);
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

} // namespace Core
