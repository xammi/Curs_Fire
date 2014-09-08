#include "int_solver.h"

namespace Core {

const int ITERS = 20;

//-------------------------------------------------------------------------------------------------
Int_NS_Solver::Int_NS_Solver(int _N, float _visc, float _diff, float _dt) :
    AbstractSolver(_N)
{
     visc = F2X(_visc);
     diff = F2X(_diff);
     dt = F2X(_dt);
}
//-------------------------------------------------------------------------------------------------
void Int_NS_Solver::add_source(freal * x, freal * s) {
    int i = 0;
    for (; i < size; i++)
        x[i] += XM(dt, s[i]);
}

void Int_NS_Solver::set_bnd(int b, freal * x) {
    int i;
    freal HALF = F2X(0.5);

    for (i = 1; i <= N; i++) {
        x[IX(0,i)] = (b==1)? -x[IX(1,i)] : x[IX(1,i)];
        x[IX(N+1,i)] = (b==1)? -x[IX(N,i)] : x[IX(N,i)];
        x[IX(i,0)] = (b==2)? -x[IX(i,1)] : x[IX(i,1)];
        x[IX(i,N+1)] = (b==2)? -x[IX(i,N)] : x[IX(i,1)];
    }
    x[IX(0,0)] = XM(HALF, (x[IX(1,0)] + x[IX(0,1)]));
    x[IX(0,N+1)] = XM(HALF, (x[IX(1,N+1)] + x[IX(0,N)]));
    x[IX(N+1,0)] = XM(HALF, (x[IX(N,0)] + x[IX(N+1,1)]));
    x[IX(N+1,N+1)] = XM(HALF, (x[IX(N,N+1)] + x[IX(N+1,N)]));
}

void Int_NS_Solver::diffuse(int b, freal * x, freal * x0) {
    int i, j, k;
    freal a = XM(dt, XM(diff, I2X(N * N)));
    freal DIVIDER = I2X(1) + XM( I2X(4), a);

    for (k = 0; k < ITERS; k++) {
        for (i = 1; i <= N; i++)
            for (j = 1; j <= N; j++)
                x[IX(i,j)] = XD((x0[IX(i,j)] + XM(a, ( x[IX(i-1,j)] + x[IX(i+1,j)] + x[IX(i,j-1)] + x[IX(i,j+1)] ))), DIVIDER);
        set_bnd(b, x);
    }
}

void Int_NS_Solver::advect(int b, freal * d, freal * d0, freal * u, freal * v) {
    int i, j, i0, j0, i1, j1;
    freal x, y, s0, t0, s1, t1, dt0;

    freal N_X = I2X(N);
    dt0 = XM(dt, N_X);
    freal HALF = F2X(0.5);

    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++) {
            x = I2X(i) - XM(dt0, u[IX(i,j)]);
            y = I2X(j) - XM(dt0, v[IX(i,j)]);

            if (x < HALF) x = HALF;
            if (x > N_X + HALF) x = N_X + HALF;
            i0 = X2I(x);
            i1 = i0 + 1;

            if (y < HALF) y = HALF;
            if (y > N_X + HALF) y = N_X + HALF;
            j0 = X2I(y);
            j1 = j0 + 1;

            s1 = x - I2X(i0);
            s0 = I2X(1) - s1;
            t1 = y - I2X(j0);
            t0 = I2X(1) - t1;

            d[IX(i,j)] = XM(s0, (XM(t0, d0[IX(i0,j0)]) + XM(t1, d0[IX(i0, j1)]))) +
                         XM(s1, (XM(t0, d0[IX(i1,j0)]) + XM(t1, d0[IX(i1,j1)])));
        }

    set_bnd(b, d);
}

void Int_NS_Solver::project(freal * u, freal * v, freal * p, freal * div) {
    int i, j, k;
    freal HALF = F2X(0.5);
    freal N_X = I2X(N);

    freal h = XD(F2X(1.0), N_X);

    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++) {
            div[IX(i,j)] = XM(-HALF, XM(h, (u[IX(i+1, j)] - u[IX(i-1, j)] + v[IX(i,j+1)] - v[IX(i,j-1)])));
            p[IX(i,j)] = I2X(0);
        }

    set_bnd(0, div);
    set_bnd(0, p);

    for (k = 0; k < ITERS; k++) {
        for (i = 1; i <= N; i++)
            for (j = 1; j <= N; j++) {
                p[IX(i,j)] = XD((div[IX(i,j)] + p[IX(i-1,j)] + p[IX(i+1,j)] + p[IX(i,j-1)] + p[IX(i,j+1)]), I2X(4));
            }
        set_bnd(0, p);
    }

    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++) {
            u[IX(i,j)] -= XM(HALF, XD((p[IX(i+1,j)] - p[IX(i-1,j)]), h));
            v[IX(i,j)] -= XM(HALF, XD((p[IX(i,j+1)] - p[IX(i,j-1)]), h));
        }

    set_bnd(1, u);
    set_bnd(2, v);
}

void Int_NS_Solver::dens_step(freal * x, freal * x0, freal * u, freal * v) {
    add_source(x, x0);
    I_SWAP(x0, x);
    diffuse(0, x, x0);
    I_SWAP(x0, x);
    advect(0, x, x0, u, v);
}

void Int_NS_Solver::vel_step(freal * u, freal * v, freal * u0, freal * v0) {
    add_source(u, u0);
    add_source(v, v0);
    I_SWAP(u0, u);
    diffuse(1, u, u0);
    I_SWAP(v0, v);
    diffuse(2, v, v0);

    project(u, v, u0, v0);
    I_SWAP(u0, u);
    I_SWAP(v0, v);
    advect(1, u, u0, u0, v0);
    advect(2, v, v0, u0, v0);
    project(u, v, u0, v0);
}

void Int_NS_Solver::solver_step(int _N, freal * dens, freal * dens0, freal * u, freal * v, freal * u0, freal * v0) {
    if (! correct_N(_N))
        throw Wrong_N();

    vel_step(u, v, u0, v0);
    dens_step(dens, dens0, u, v);
}

void Int_NS_Solver::solver_step(int _N, const Int_NS_Grid & grid) {
    solver_step(_N, grid.dens, grid.dens_src, grid.u, grid.v, grid.u_src, grid.v_src);
}

//-------------------------------------------------------------------------------------------------
} // namespace Core
