#include "FlameGrid.h"

namespace Core {
//-------------------------------------------------------------------------------------------------
void FlameGrid::set_density_src(int dens_src_power) {
    FVal POSIT = F2X(transVal(-80, 80, dens_src_power));

    for (int I = 5; I <= N-4; I++)
        for (int J = 1; J <= 3; J++) {
            dens_src[I][J] = POSIT;
        }
}

void FlameGrid::set_velocity_src(int v_up, int v_side) {
    FVal UP = F2X(transVal(0.1, 1, v_up));
    FVal DOWN = F2X(transVal(-5, 1, v_side));

    for (int I = 1; I < N/2; ++I)
        for (int J = N - 3; J <= N; ++J) {
            u[I][J] = DOWN;
            u[N-I+1][J] = -DOWN;
        }

    for (int I = 0; I <= 2; I++)
        for (int J = N-10; J <= N-4; J++) {
            v[I][J] = DOWN;
            v[N-I+1][J] = DOWN;
        }

    for (int I = 3; I <= N-2; I++)
        for (int J = 20; J <= N-10; J++) {
            v[I][J] = UP;
        }
}

void FlameGrid::fluctuations(int v_flucts, int u_flucts) {
    float vf = transVal(0.1, 5, v_flucts);
    fill_random(v_src, -vf, vf);

    float uf = transVal(0.0, 0.1, u_flucts);
    fill_random(u_src, -uf, uf);
}

QColor FlameGrid::color(const int degree) const {
    if (degree < 1)
        return QColor(255, 255, 255, 0);
    return QColor(200, 140, 0, degree);
}
//-------------------------------------------------------------------------------------------------
} // namespace Core
