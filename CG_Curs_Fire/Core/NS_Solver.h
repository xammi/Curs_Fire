#ifndef ENGINE_H
#define ENGINE_H

#include "AbstractSolver.h"
#include "NS_Grid.h"

namespace Core {

//-------------------------------------------------------------------------------------------------
// NS = Navier-Stokes
class NS_Solver : public AbstractSolver
{
public:
    NS_Solver(int _N, float _visc, float _diff, float _dt);

    void solver_step(int _N, const NS_Grid &);
    void solver_step(int _N, Field x, Field x0, Field u, Field v, Field u0, Field v0);

    void set_params(float _visc, float _diff, float _dt);

protected:
    // general solver utils
    void add_source(Field field, Field source);
    void set_bnd(int B, Field x);

    // density solver
    void diffuse(int B, Field x, Field x0);
    void advect(int B, Field d, Field d0, Field u, Field v);
    void dens_step(Field x, Field x0, Field u, Field v);

    // velocity solver
    void project(Field u, Field v, Field p, Field div);
    void vel_step(Field u, Field v, Field u0, Field v0);

protected:
    Factor visc;
    Factor diff;
    Factor dt;
};
//-------------------------------------------------------------------------------------------------

} // namespace Core

#endif // ENGINE_H
