#ifndef INT_GRID_H
#define INT_GRID_H

#include "../agrid.h"

#include <QColor>
#include <QPainter>

namespace Core {

#define IX(i, j) ((i) + (N+2) * (j))

// Special macroses
typedef long freal;
#define FPP 9
#define X1_0 (1 << FPP)

// conversions for freal
#define I2X(x) ( (freal) ((x) << FPP) )
#define F2X(x) ( (freal) ((x) * X1_0) )
#define X2I(x) ( (int) ((x) >> FPP) )
#define X2F(x) ( (float) (x) / X1_0 )

// replacements for the multiplication and division
#define XM(x, y) ( (freal) (((x) * (y)) >> FPP) )
#define XD(x, y) ( (freal) ( (((x)) << FPP) / (y) ) )

//-------------------------------------------------------------------------------------------------
class Int_NS_Grid : public AbstractGrid
{
    friend class Int_NS_Solver;

public:
    Int_NS_Grid(const int);
    ~Int_NS_Grid();

    void set_src();
    void fluctuations();

    freal density(int i, int j) const;
    freal min_dens() const;
    freal max_dens() const;

    void draw(QPainter &);

private:
    void fill_random(freal * src, freal from, freal to);

    void set_conf();
    void dispose_conf();

    void set_density_src();
    void set_velocity_src();
    void set_random_src();

    // params: degree
    QColor w_black(const int) const;
    QColor w_yellow(const int) const;

private:
    freal * u, * u_src;
    freal * v, * v_src;
    freal * dens, * dens_src;
};
//-------------------------------------------------------------------------------------------------

} // namespace Core

#endif // INT_GRID_H
