#ifndef FLAME_H
#define FLAME_H

#include "../Geometry/Drawable.h"
#include "NS_Grid.h"
#include "NS_Solver.h"

using Core::NS_Grid;
using Core::NS_Solver;

//-------------------------------------------------------------------------------------------------
class FlameGrid : public NS_Grid
{
    friend class NS_Solver;

public:
    FlameGrid(const int _N) : NS_Grid(_N) {}
    ~FlameGrid() {}

    void set_density_src();
    void set_velocity_src();
    void fluctuations();
};

//-------------------------------------------------------------------------------------------------

class Flame : public Drawable, public QRunnable
{
public:
    Flame();
    Flame(double lX, double rX, double lY, double rY, double lZ, double rZ);
    ~Flame();

    void draw(QPainter &, const Projector &, const Plane3D &);
    void updateByTimer();
    void specialAction();

    void run();

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
