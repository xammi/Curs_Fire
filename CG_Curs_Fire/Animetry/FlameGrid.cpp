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
    int min = 0,
        deg_unu = 150,
        deg_du = 215,
        max = 255;

    if (degree <= min) {
        return QColor(max, max, max, min);
    }
    else if (degree <= deg_unu) {
        return QColor(200, 140, min, degree + 105);
    }
    else if (degree <= deg_du) {
        int unu = 200,
            du = 106,
            alpha = 235;

        double deg_diff = qAbs(deg_du - deg_unu),
               diff = qAbs(unu - du);

        int B_channel = unu - qRound(diff / deg_diff * (degree - deg_unu));
        return QColor(max, B_channel, min, alpha);
    }
    else if (degree <= max) {
        int unu = 106,
            du = 34,
            alpha = 235;

        double deg_diff = qAbs(max - deg_du),
               diff = qAbs(du - unu);

        int B_channel = unu - qRound(diff / deg_diff * (degree - deg_du));
        return QColor(max, B_channel, min, alpha);
    }
    return QColor(200, 140, min, max);
}
//-------------------------------------------------------------------------------------------------
} // namespace Core
