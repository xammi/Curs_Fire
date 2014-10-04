#ifndef SMOKE_H
#define SMOKE_H

#include "../Geometry/Drawable.h"
#include "NS_Grid.h"
#include "NS_Solver.h"

using Core::NS_Grid;
using Core::NS_Solver;

//-------------------------------------------------------------------------------------------------

class Smoke : public Drawable
{
public:
    Smoke();
    Smoke(double lX, double rX, double lY, double rY, double lZ, double rZ);
    ~Smoke();

    void draw(QPainter &, const Projector &, const Plane3D &);
    void updateByTimer();

protected:
    void initialize();
    QColor w_black(const int) const;

private:
    NS_Solver * solver;
    NS_Grid * grid;
    int N;
};

//-------------------------------------------------------------------------------------------------

#endif // SMOKE_H
