#include "SmokeGrid.h"

namespace Core {
//-------------------------------------------------------------------------------------------------
void SmokeGrid::set_density_src(int dens_src_power) {
    FVal POSIT = F2X(transVal(-20, 40, dens_src_power));

    for (int I = 5; I <= N-4; I++)
        for (int J = 1; J <= 3; J++) {
            dens_src[I][J] = POSIT;
        }
}

void SmokeGrid::set_velocity_src(int v_up, int) {
    FVal UP = F2X(transVal(0, 8, v_up));

    for (int I = 3; I <= N-2; I++)
        for (int J = 20; J <= N-10; J++) {
            v[I][J] = UP;
        }
}

void SmokeGrid::fluctuations(int v_flucts, int) {
    float vf = transVal(0.1, 3, v_flucts);
    fill_random(u_src, -vf, vf);
}

QColor SmokeGrid::color(const int degree) const {
    if (degree < 1 || degree > 255)
        return QColor(255, 255, 255, 0);
    int icolor = degree;
    return QColor(icolor, icolor, icolor, icolor);
}
//-------------------------------------------------------------------------------------------------
} // namespace Core
