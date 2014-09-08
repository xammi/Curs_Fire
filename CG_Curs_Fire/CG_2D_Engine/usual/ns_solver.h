#ifndef ENGINE_H
#define ENGINE_H

#include "../asolver.h"
#include "ns_grid.h"

namespace Core {

#define F_SWAP(x0, x) { float * tmp = x0; x0 = x; x = tmp; }

//-------------------------------------------------------------------------------------------------
// NS = Navier-Stokes
class NS_Solver : public AbstractSolver
{
public:
    NS_Solver(int _N, float _visc, float _diff, float _dt);

    void solver_step(int _N, const NS_Grid &);
    void solver_step(int _N, float * x, float * x0, float * u, float * v, float * u0, float * v0);

protected:
    // general solver utils
    void add_source(float * x, float * s);
    void set_bnd(int b, float * x);

    // density solver
    void diffuse(int b, float * x, float * x0);
    void advect(int b, float * d, float * d0, float * u, float * v);
    void dens_step(float * x, float * x0, float * u, float * v);

    // velocity solver
    void project(float * u, float * v, float * p, float * div);
    void vel_step(float * u, float * v, float * u0, float * v0);

protected:
    float visc;
    float diff;
    float dt;
};
//-------------------------------------------------------------------------------------------------

} // namespace Core

#endif // ENGINE_H
