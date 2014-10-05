#ifndef NS_GRID_H
#define NS_GRID_H

#include "AbstractGrid.h"

#include <QColor>

namespace Core {

#define IX(i, j) ((i)+(N+2)*(j))
#define I2F(x) ((float)(x))

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

    float density(int i, int j) const;
    float min_dens() const;
    float max_dens() const;

protected:
    void fill_random(float * src, float from, float to);

    void set_conf();
    void dispose_conf();

protected:
    float * u, * u_src;
    float * v, * v_src;
    float * dens, * dens_src;
};
//-------------------------------------------------------------------------------------------------

} // namespace Core

#endif // NS_GRID_H
