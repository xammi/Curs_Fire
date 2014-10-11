#ifndef SMOKEGRID_H
#define SMOKEGRID_H

#include "../Core/NS_Grid.h"

namespace Core {
//-------------------------------------------------------------------------------------------------
class SmokeGrid : public NS_Grid
{
    friend class NS_Solver;

public:
    SmokeGrid(const int _N) : NS_Grid(_N) {}
    ~SmokeGrid() {}

    void set_density_src(int);
    void set_velocity_src(int, int);
    void fluctuations(int, int);
};
//-------------------------------------------------------------------------------------------------
} // namespace Core

#endif // SMOKEGRID_H
