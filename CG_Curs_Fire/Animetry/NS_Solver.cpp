#include "NS_Solver.h"

namespace Core {

const int ITERS = 20;

NS_Solver::NS_Solver(int _N, Factor _visc, Factor _diff, Factor _dt) :
    AbstractSolver(_N), visc(_visc), diff(_diff), dt(_dt)
{}
//-------------------------------------------------------------------------------------------------
void NS_Solver::add_source(Field field, Field source) {
    int I, J, N_1 = N + 1;
    for (I = 1; I <= N; I++)
        for (J = 1; J <= N; J++)
            field[I][J] += dt * source[I][J];
}

void NS_Solver::set_bnd(int B, Field x) {
    int N_1 = N + 1;

    for (int I = 1; I <= N; I++) {
        x[0][I] = (B==1)? -x[1][I] : x[1][I];
        x[N_1][I] = (B==1)? -x[N][I] : x[N][I];
        x[I][0] = (B==2)? -x[I][1] : x[I][1];
        x[I][N_1] = (B==2)? -x[I][N] : x[I][1];
    }
    x[0][0] = 0.5 * (x[1][0] + x[0][1]);
    x[0][N_1] = 0.5 * (x[1][N_1] + x[0][N]);
    x[N_1][0] = 0.5 * (x[N][0] + x[N_1][1]);
    x[N_1][N_1] = 0.5 * (x[N][N_1] + x[N_1][N]);
}

void NS_Solver::diffuse(int B, Field x, Field x0) {
    int I, J, K;
    Factor A = dt * diff * N * N;
    Factor DIVIDER = 1 + 4*A;

    for (K = 0; K < ITERS; K++) {
        for (I = 1; I <= N; I++)
            for (J = 1; J <= N; J++)
                x[I][J] = (x0[I][J] + A*( x[I-1][J] + x[I+1][J] + x[I][J-1] + x[I][J+1] )) / DIVIDER;
        set_bnd(B, x);
    }
}

void NS_Solver::advect(int B, Field d, Field d0, Field u, Field v) {
    int I, J, I0, J0, I1, J1;
    Factor x, y, s0, t0, s1, t1, dt0;

    dt0 = dt * N;
    for (I = 1; I <= N; I++)
        for (J = 1; J <= N; J++) {
            x = I - dt0 * u[I][J];
            y = J - dt0 * v[I][J];
            
            if (x < 0.5) x = 0.5;
            if (x > N + 0.5) x = N + 0.5;
            I0 = (int) x;
            I1 = I0 + 1;

            if (y < 0.5) y = 0.5;
            if (y > N + 0.5) y = N + 0.5;
            J0 = (int) y;
            J1 = J0 + 1;

            s1 = x - I0;
            s0 = 1 - s1;
            t1 = y - J0;
            t0 = 1 - t1;

            d[I][J] = s0 * (t0 * d0[I0][J0] + t1 * d0[I0][J1]) +
                      s1 * (t0 * d0[I1][J0] + t1 * d0[I1][J1]);
        }

    set_bnd(B, d);
}

void NS_Solver::project(Field u, Field v, Field p, Field div) {
    int I, J, K;
    Factor H = 1.0 / N;

    for (I = 1; I <= N; I++)
        for (J = 1; J <= N; J++) {
            div[I][J] = -0.5 * H * (u[I+1][J] - u[I-1][J] + v[I][J+1] - v[I][J-1]);
            p[I][J] = 0;
        }

    set_bnd(0, div);
    set_bnd(0, p);

    for (K = 0; K < ITERS; K++) {
        for (I = 1; I <= N; I++)
            for (J = 1; J <= N; J++) {
                p[I][J] = (div[I][J] + p[I-1][J] + p[I+1][J] + p[I][J-1] + p[I][J+1]) / 4;
            }
        set_bnd(0, p);
    }

    for (I = 1; I <= N; I++)
        for (J = 1; J <= N; J++) {
            u[I][J] -= 0.5 * (p[I+1][J] - p[I-1][J]) / H;
            v[I][J] -= 0.5 * (p[I][J+1] - p[I][J-1]) / H;
        }

    set_bnd(1, u);
    set_bnd(2, v);
}

void NS_Solver::dens_step(Field x, Field x0, Field u, Field v) {
    add_source(x, x0);
    F_SWAP(x0, x);
    diffuse(0, x, x0);
    F_SWAP(x0, x);
    advect(0, x, x0, u, v);
}

void NS_Solver::vel_step(Field u, Field v, Field u0, Field v0) {
    add_source(u, u0);
    add_source(v, v0);
    F_SWAP(u0, u);
    diffuse(1, u, u0);
    F_SWAP(v0, v);
    diffuse(2, v, v0);

    project(u, v, u0, v0);
    F_SWAP(u0, u);
    F_SWAP(v0, v);
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
