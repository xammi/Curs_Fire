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
    void initialize();

    // float: min, float: factor
    void draw_XY(QPainter &, const Projector &, double Z, float, float);
    void draw_ZY(QPainter &, const Projector &, double X, float, float);
    void draw_XZ(QPainter &, const Projector &, double Y, float, float);

    void drawPolygon(const Polygon3D &, QPainter &, const Projector &);

private:
    Type type;
    NS_Solver * solver;
    NS_Grid * grid;
    int N;
};

//-------------------------------------------------------------------------------------------------

#endif // FLUID_H
