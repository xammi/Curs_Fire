#ifndef SMOKE_H
#define SMOKE_H

#include "../Geometry/Drawable.h"
#include "NS_Grid.h"
#include "NS_Solver.h"
#include "Flame.h"

using Core::NS_Grid;
using Core::NS_Solver;

//-------------------------------------------------------------------------------------------------
class SmokeGrid : public NS_Grid
{
    friend class NS_Solver;

public:
    SmokeGrid(const int _N) : NS_Grid(_N) {}
    ~SmokeGrid() {}

    void set_density_src();
    void set_velocity_src();
    void fluctuations();
};
//-------------------------------------------------------------------------------------------------

class Smoke : public Drawable, public QRunnable
{
public:
    Smoke();
    Smoke(double lX, double rX, double lY, double rY, double lZ, double rZ, Flame *);
    ~Smoke();

    void draw(QPainter &, const Projector &, const Plane3D &);
    void updateByTimer();
    void specialAction();

    void run();

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
