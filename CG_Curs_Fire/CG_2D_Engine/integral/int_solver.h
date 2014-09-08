#ifndef INT_SOLVER_H
#define INT_SOLVER_H

#include "../asolver.h"
#include "int_grid.h"

namespace Core {

#define I_SWAP(x0, x) { freal * tmp = x0; x0 = x; x = tmp; }

//-------------------------------------------------------------------------------------------------
/*
 * The Integral implementation of the Navier-Stocks Solver.
*/
class Int_NS_Solver : public AbstractSolver
{
public:
    Int_NS_Solver(int _N, float _visc, float _diff, float _dt);

    void solver_step(int _N, const Int_NS_Grid &);
    void solver_step(int _N, freal * x, freal * x0, freal * u, freal * v, freal * u0, freal * v0);

protected:
    // general solver utils
    void add_source(freal * x, freal * s);
    void set_bnd(int b, freal * x);

    // density solver
    void diffuse(int b, freal * x, freal * x0);
    void advect(int b, freal * d, freal * d0, freal * u, freal * v);
    void dens_step(freal * x, freal * x0, freal * u, freal * v);

    // velocity solver
    void project(freal * u, freal * v, freal * p, freal * div);
    void vel_step(freal * u, freal * v, freal * u0, freal * v0);

protected:
    freal visc;
    freal diff;
    freal dt;
};
//-------------------------------------------------------------------------------------------------
} // namespace Core

#endif // INT_SOLVER_H
