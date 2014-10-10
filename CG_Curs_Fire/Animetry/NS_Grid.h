#ifndef NS_GRID_H
#define NS_GRID_H

#include "AbstractGrid.h"

#include <QColor>

namespace Core {

//-------------------------------------------------------------------------------------------------
class NS_Grid : public AbstractGrid
{
    friend class NS_Solver;

public:
    NS_Grid(const int);
    virtual ~NS_Grid();

    virtual void set_density_src() = 0;
    virtual void set_velocity_src() = 0;
    virtual void fluctuations() = 0;

    FVal density(int i, int j) const;
    FVal min_dens() const;
    FVal max_dens() const;

protected:
    void fill_random(Field src, FVal from, FVal to);

    void set_fields();
    void dispose_fields();

    Field alloc() const;
    void dealloc(Field);

protected:
    Field u;
    Field u_src;
    Field v;
    Field v_src;
    Field dens;
    Field dens_src;
};
//-------------------------------------------------------------------------------------------------

} // namespace Core

#endif // NS_GRID_H
