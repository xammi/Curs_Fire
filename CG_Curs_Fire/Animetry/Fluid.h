#ifndef FLUID_H
#define FLUID_H

#include "../Geometry/Drawable.h"
#include "../Core/NS_Solver.h"

#include "FlameGrid.h"
#include "SmokeGrid.h"
#include "Adjustable.h"

using Core::NS_Grid;
using Core::FlameGrid;
using Core::SmokeGrid;
using Core::NS_Solver;

//-------------------------------------------------------------------------------------------------

class Fluid : public Drawable, public Adjustable
{
public:
    enum Type { FLAME, SMOKE };

public:
    Fluid();
    Fluid(double lX, double rX, double lY, double rY, double lZ, double rZ, Type);
    ~Fluid();

    void draw(QPainter &, const Projector &, const Plane3D &);
    void updateByTimer();
    void specialAction();

    void withSet();

protected:
    void initialize(const Type type);

private:
    NS_Solver * solver;
    NS_Grid * grid;
    int N;
};

//-------------------------------------------------------------------------------------------------

#endif // FLUID_H
