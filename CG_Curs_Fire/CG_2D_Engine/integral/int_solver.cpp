#include "int_solver.h"

namespace Core {

const int ITERS = 20;

//-------------------------------------------------------------------------------------------------
Int_NS_Solver::Int_NS_Solver(int _N, float _visc, float _diff, float _dt) :
    AbstractSolver(_N), visc(_visc), diff(_diff), dt(_dt)
{

}
//-------------------------------------------------------------------------------------------------
void Int_NS_Solver::add_source(float * x, float * s) {
    int i = 0;
    for (; i < size; i++)
        x[i] += dt * s[i];
}

void Int_NS_Solver::set_bnd(int b, float * x) {
    int i;

    for (i = 1; i <= N; i++) {
        x[IX(0,i)] = (b==1)? -x[IX(1,i)] : x[IX(1,i)];
        x[IX(N+1,i)] = (b==1)? -x[IX(N,i)] : x[IX(N,i)];
        x[IX(i,0)] = (b==2)? -x[IX(i,1)] : x[IX(i,1)];
        x[IX(i,N+1)] = (b==2)? -x[IX(i,N)] : x[IX(i,1)];
    }
    x[IX(0,0)] = 0.5 * (x[IX(1,0)] + x[IX(0,1)]);
    x[IX(0,N+1)] = 0.5 * (x[IX(1,N+1)] + x[IX(0,N)]);
    x[IX(N+1,0)] = 0.5 * (x[IX(N,0)] + x[IX(N+1,1)]);
    x[IX(N+1,N+1)] = 0.5 * (x[IX(N,N+1)] + x[IX(N+1,N)]);
}

void Int_NS_Solver::diffuse(int b, float * x, float * x0) {
    int i, j, k;
    float a = dt * diff * N * N;

    for (k = 0; k < ITERS; k++) {
        for (i = 1; i <= N; i++)
            for (j = 1; j <= N; j++)
                x[IX(i,j)] = (x0[IX(i,j)] + a*( x[IX(i-1,j)] + x[IX(i+1,j)] + x[IX(i,j-1)] + x[IX(i,j+1)] )) / (1 + 4*a);
        set_bnd(b, x);
    }
}

void Int_NS_Solver::advect(int b, float * d, float * d0, float * u, float * v) {
    int i, j, i0, j0, i1, j1;
    float x, y, s0, t0, s1, t1, dt0;

    dt0 = dt * N;
    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++) {
            x = i - dt0 * u[IX(i,j)];
            y = j - dt0 * v[IX(i,j)];

            if (x < 0.5) x = 0.5;
            if (x > N + 0.5) x = N + 0.5;
            i0 = (int) x;
            i1 = i0 + 1;

            if (y < 0.5) y = 0.5;
            if (y > N + 0.5) y = N + 0.5;
            j0 = (int) y;
            j1 = j0 + 1;

            s1 = x - i0;
            s0 = 1 - s1;
            t1 = y - j0;
            t0 = 1 - t1;

            d[IX(i,j)] = s0 * (t0 * d0[IX(i0,j0)] + t1 * d0[IX(i0, j1)]) +
                         s1 * (t0 * d0[IX(i1,j0)] + t1 * d0[IX(i1,j1)]);
        }

    set_bnd(b, d);
}

void Int_NS_Solver::project(float * u, float * v, float * p, float * div) {
    int i, j, k;
    float h = 1.0 / N;

    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++) {
            div[IX(i,j)] = -0.5 * h * (u[IX(i+1, j)] - u[IX(i-1, j)] + v[IX(i,j+1)] - v[IX(i,j-1)]);
            p[IX(i,j)] = 0;
        }

    set_bnd(0, div);
    set_bnd(0, p);

    for (k = 0; k < ITERS; k++) {
        for (i = 1; i <= N; i++)
            for (j = 1; j <= N; j++) {
                p[IX(i,j)] = (div[IX(i,j)] + p[IX(i-1,j)] + p[IX(i+1,j)] + p[IX(i,j-1)] + p[IX(i,j+1)]) / 4;
            }
        set_bnd(0, p);
    }

    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++) {
            u[IX(i,j)] -= 0.5 * (p[IX(i+1,j)] - p[IX(i-1,j)]) / h;
            v[IX(i,j)] -= 0.5 * (p[IX(i,j+1)] - p[IX(i,j-1)]) / h;
        }

    set_bnd(1, u);
    set_bnd(2, v);
}

void Int_NS_Solver::dens_step(float * x, float * x0, float * u, float * v) {
    add_source(x, x0);
    SWAP(x0, x);
    diffuse(0, x, x0);
    SWAP(x0, x);
    advect(0, x, x0, u, v);
}

void Int_NS_Solver::vel_step(float * u, float * v, float * u0, float * v0) {
    add_source(u, u0);
    add_source(v, v0);
    SWAP(u0, u);
    diffuse(1, u, u0);
    SWAP(v0, v);
    diffuse(2, v, v0);

    project(u, v, u0, v0);
    SWAP(u0, u);
    SWAP(v0, v);
    advect(1, u, u0, u0, v0);
    advect(2, v, v0, u0, v0);
    project(u, v, u0, v0);
}

void Int_NS_Solver::solver_step(int _N, float * dens, float * dens0, float * u, float * v, float * u0, float * v0) {
    if (! correct_N(_N))
        throw Wrong_N();

    vel_step(u, v, u0, v0);
    dens_step(dens, dens0, u, v);
}

void Int_NS_Solver::solver_step(int _N, const Int_NS_Grid &grid) {
    solver_step(_N, grid.dens, grid.dens_src, grid.u, grid.v, grid.u_src, grid.v_src);
}

//-------------------------------------------------------------------------------------------------
} // namespace Core
