#ifndef FLAMEGRID_H
#define FLAMEGRID_H

#include "../Core/NS_Grid.h"

namespace Core {

//-------------------------------------------------------------------------------------------------
class FlameGrid : public NS_Grid
{
    friend class NS_Solver;

public:
    FlameGrid(const int _N) : NS_Grid(_N) {}
    ~FlameGrid() {}

    void set_density_src(int);
    void set_velocity_src(int, int);
    void fluctuations(int, int);
};
//-------------------------------------------------------------------------------------------------
} // namespace Core

#endif // FLAMEGRID_H
