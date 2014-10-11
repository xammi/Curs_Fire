#ifndef FLAME_H
#define FLAME_H

#include "../Geometry/Drawable.h"
#include "../Core/NS_Solver.h"

#include "FlameGrid.h"
#include "Adjustable.h"

using Core::NS_Grid;
using Core::FlameGrid;
using Core::NS_Solver;

//-------------------------------------------------------------------------------------------------

class Flame : public Drawable, public Adjustable
{
public:
    Flame();
    Flame(double lX, double rX, double lY, double rY, double lZ, double rZ);
    ~Flame();

    void draw(QPainter &, const Projector &, const Plane3D &);
    void updateByTimer();
    void specialAction();

    void withSet();

protected:
    void initialize();
    QColor w_yellow(const int) const;

private:
    NS_Solver * solver;
    NS_Grid * grid;
    int N;
};

//-------------------------------------------------------------------------------------------------

#endif // FLAME_H
