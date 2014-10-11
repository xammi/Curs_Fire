#include "NS_Solver.h"

namespace Core {

const int ITERS = 10;

NS_Solver::NS_Solver(int _N, float _visc, float _diff, float _dt) :
    AbstractSolver(_N)
{
    set_params(_visc, _diff, _dt);
}

void NS_Solver::set_params(float _visc, float _diff, float _dt) {
    visc = F2X(_visc);
    diff = F2X(_diff);
    dt = F2X(_dt);
}

//-------------------------------------------------------------------------------------------------
void NS_Solver::add_source(Field field, Field source) {
    int I, J, N_1 = N + 1;
    for (I = 0; I <= N_1; I++)
        for (J = 0; J <= N_1; J++)
            field[I][J] += XM(dt, source[I][J]);
}

void NS_Solver::set_bnd(int B, Field x) {
    int N_1 = N + 1;
    Factor HALF = F2X(0.5);

    for (int I = 1; I <= N; I++) {
        x[0][I] = (B==1)? -x[1][I] : x[1][I];
        x[N_1][I] = (B==1)? -x[N][I] : x[N][I];
        x[I][0] = (B==2)? -x[I][1] : x[I][1];
        x[I][N_1] = (B==2)? -x[I][N] : x[I][1];
    }
    x[0][0] = XM(HALF, (x[1][0] + x[0][1]));
    x[0][N_1] = XM(HALF, (x[1][N_1] + x[0][N]));
    x[N_1][0] = XM(HALF, (x[N][0] + x[N_1][1]));
    x[N_1][N_1] = XM(HALF, (x[N][N_1] + x[N_1][N]));
}

void NS_Solver::diffuse(int B, Field x, Field x0) {
    int I, J, K;
    Factor A = XM(dt, XM(diff, I2X(N * N)));
    Factor DIVIDER = I2X(1) + XM(I2X(4), A);

    for (K = 0; K < ITERS; K++) {
        for (I = 1; I <= N; I++)
            for (J = 1; J <= N; J++)
                x[I][J] = XD((x0[I][J] + XM(A, ( x[I-1][J] + x[I+1][J] + x[I][J-1] + x[I][J+1] ))), DIVIDER);
        set_bnd(B, x);
    }
}

void NS_Solver::advect(int B, Field d, Field d0, Field u, Field v) {
    int I, J, I0, J0, I1, J1;
    Factor x, y, s0, t0, s1, t1;

    Factor N_X = I2X(N),
           dt0 = XM(dt, N_X),
           HALF = F2X(0.5),
           N_HALF = N_X + HALF;

    for (I = 1; I <= N; I++)
        for (J = 1; J <= N; J++) {
            x = I2X(I) - XM(dt0, u[I][J]);
            y = I2X(J) - XM(dt0, v[I][J]);

            if (x < HALF) x = HALF;
            if (x > N_HALF) x = N_HALF;
            I0 = X2I(x);
            I1 = I0 + 1;

            if (y < HALF) y = HALF;
            if (y > N_HALF) y = N_HALF;
            J0 = X2I(y);
            J1 = J0 + 1;

            s1 = x - I2X(I0);
            s0 = I2X(1) - s1;
            t1 = y - I2X(J0);
            t0 = I2X(1) - t1;

            d[I][J] = XM(s0, (XM(t0, d0[I0][J0]) + XM(t1, d0[I0][J1]))) +
                      XM(s1, (XM(t0, d0[I1][J0]) + XM(t1, d0[I1][J1])));
        }

    set_bnd(B, d);
}

void NS_Solver::project(Field u, Field v, Field p, Field div) {
    int I, J, K;
    Factor HALF = F2X(0.5),
           N_X = I2X(N);

    Factor H = XD(F2X(1.0), N_X),
           H_HALF = XM(-HALF, H);

    for (I = 1; I <= N; I++)
        for (J = 1; J <= N; J++) {
            div[I][J] = XM(H_HALF, (u[I+1][J] - u[I-1][J] + v[I][J+1] - v[I][J-1]));
            p[I][J] = I2X(0);
        }

    set_bnd(0, div);
    set_bnd(0, p);

    Factor FOUR = I2X(4);
    for (K = 0; K < ITERS; K++) {
        for (I = 1; I <= N; I++)
            for (J = 1; J <= N; J++) {
                p[I][J] = XD((div[I][J] + p[I-1][J] + p[I+1][J] + p[I][J-1] + p[I][J+1]), FOUR);
            }
        set_bnd(0, p);
    }

    for (I = 1; I <= N; I++)
        for (J = 1; J <= N; J++) {
            u[I][J] -= XD( XM(HALF, (p[I+1][J] - p[I-1][J])), H);
            v[I][J] -= XD( XM(HALF, (p[I][J+1] - p[I][J-1])), H);
        }

    set_bnd(1, u);
    set_bnd(2, v);
}

void NS_Solver::dens_step(Field x, Field x0, Field u, Field v) {
    add_source(x, x0);
    swap(x0, x);
    diffuse(0, x, x0);
    swap(x0, x);
    advect(0, x, x0, u, v);
}

void NS_Solver::vel_step(Field u, Field v, Field u0, Field v0) {
    add_source(u, u0);
    add_source(v, v0);
    swap(u0, u);
    diffuse(1, u, u0);
    swap(v0, v);
    diffuse(2, v, v0);

    project(u, v, u0, v0);
    swap(u0, u);
    swap(v0, v);
    advect(1, u, u0, u0, v0);
    advect(2, v, v0, u0, v0);
    project(u, v, u0, v0);
}

void NS_Solver::solver_step(int _N, Field dens, Field dens0, Field u, Field v, Field u0, Field v0) {
    if (! correct_N(_N))
        throw Wrong_N();

    vel_step(u, v, u0, v0);
    dens_step(dens, dens0, u, v);
}

void NS_Solver::solver_step(int _N, const NS_Grid & grid) {
    solver_step(_N, grid.dens, grid.dens_src, grid.u, grid.v, grid.u_src, grid.v_src);
}

//-------------------------------------------------------------------------------------------------
} // namespace Core
