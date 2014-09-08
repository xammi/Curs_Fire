#ifndef NS_GRID_H
#define NS_GRID_H

#include "../agrid.h"

#include <QColor>
#include <QPainter>

namespace Core {

#define IX(i, j) ((i) + (N+2) * (j))

//-------------------------------------------------------------------------------------------------
class NS_Grid : public AbstractGrid
{
    friend class NS_Solver;

public:
    NS_Grid(const int);
    ~NS_Grid();

    void set_src();
    void fluctuations();

    bool correct_N(int _N) const { return N == _N; }

    float density(int i, int j) const;
    float min_dens() const;
    float max_dens() const;

    void draw(QPainter &);

private:
    void set_conf();
    void dispose_conf();

    void set_density_src();
    void set_velocity_src();
    void set_random_src();

    // params: degree
    QColor w_black(const int) const;
    QColor w_yellow(const int) const;

private:
    int N;
    int size;

    float * u, * u_src;
    float * v, * v_src;
    float * dens, * dens_src;
};
//-------------------------------------------------------------------------------------------------

} // namespace Core

#endif // NS_GRID_H
