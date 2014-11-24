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

    virtual void set_density_src(int) = 0;
    virtual void set_velocity_src(int, int) = 0;
    virtual void fluctuations(int, int) = 0;

    virtual QColor color(const int degree) const = 0;

    float density(int i, int j) const;
    float min_dens() const;
    float max_dens() const;

    void to_zero();

protected:
    void fill_random(Field src, float from, float to);

    void set_fields();
    void dispose_fields();

    Field alloc() const;
    void dealloc(Field);

    void to_zero(Field);

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
