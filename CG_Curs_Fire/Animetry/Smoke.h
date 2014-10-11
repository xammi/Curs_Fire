#ifndef SMOKE_H
#define SMOKE_H

#include "../Geometry/Drawable.h"
#include "../Core/NS_Solver.h"

#include "Flame.h"
#include "SmokeGrid.h"
#include "Adjustable.h"

using Core::NS_Grid;
using Core::SmokeGrid;
using Core::NS_Solver;

//-------------------------------------------------------------------------------------------------

class Smoke : public Drawable, public Adjustable
{
public:
    Smoke();
    Smoke(double lX, double rX, double lY, double rY, double lZ, double rZ, Flame *);
    ~Smoke();

    void draw(QPainter &, const Projector &, const Plane3D &);
    void updateByTimer();
    void specialAction();

    void withSet();

protected:
    void initialize();
    QColor w_black(const int) const;

private:
    Flame * flame;
    NS_Solver * solver;
    NS_Grid * grid;

    int N;
};

//-------------------------------------------------------------------------------------------------

#endif // SMOKE_H
