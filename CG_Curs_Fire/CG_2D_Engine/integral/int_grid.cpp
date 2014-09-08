#include "int_grid.h"
#include "time.h"

namespace Core {

//-------------------------------------------------------------------------------------------------
Int_NS_Grid::Int_NS_Grid(const int _N) :
    AbstractGrid(_N)
{
    uint T = time(NULL);
    qsrand(T);

    set_conf();
    set_src();
}

Int_NS_Grid::~Int_NS_Grid() {
    dispose_conf();
}

void Int_NS_Grid::dispose_conf() {
    if (u) delete [] u;
    if (v) delete [] v;
    if (dens) delete [] dens;

    if (u_src) delete [] u_src;
    if (v_src) delete [] v_src;
    if (dens_src) delete [] dens_src;
}

void Int_NS_Grid::set_conf() {
    u = new freal[size];
    v = new freal[size];
    dens = new freal[size];

    u_src = new freal[size];
    v_src = new freal[size];
    dens_src = new freal[size];

    if (!u || !v || !dens || !u_src || !v_src || !dens_src)
        throw MemNotAlloc();
}

freal Int_NS_Grid::density(int i, int j) const {
    return dens[IX(i, j)];
}

freal Int_NS_Grid::min_dens() const {
    return get_min(size, dens);
}

freal Int_NS_Grid::max_dens() const {
    return get_max(size, dens);
}

void Int_NS_Grid::fill_random(freal * src, freal from, freal to) {
    freal factor = to - from;
    freal MAX_RAND = I2X(RAND_MAX);

    for (int i = 0; i < size; i++) {
         freal num = I2X(qrand());
         src[i] = XD(num, XM(MAX_RAND, factor)) + from;
    }
}
//-------------------------------------------------------------------------------------------------
void Int_NS_Grid::set_src() {
    set_density_src();
    set_velocity_src();
//    set_random_src();
}

void Int_NS_Grid::set_density_src() {
    freal POSIT = I2X(50);
    freal NEGAT_SIDE = I2X(0);
    freal NEGAT_TOP = I2X(0);

    for (int I = 10; I <= N - 10; I++)
        dens_src[IX(N, I)] = POSIT;

    for (int I = 1; I < N - 1; I++) {
        dens_src[IX(I, 1)] = NEGAT_SIDE;
        dens_src[IX(I, N)] = NEGAT_SIDE;
    }

    for (int I = 10; I <= N-10; I++)
        dens_src[IX(30, I)] = NEGAT_TOP;
}

void Int_NS_Grid::set_velocity_src() {
    freal UP = I2X(-10);

    for (int I = 1; I <= N; I++)
        for (int J = 1; J <= N; J++) {
            u_src[IX(I,J)] = UP;
        }
}

void Int_NS_Grid::set_random_src() {
    fill_random(u_src, I2X(-5), I2X(5));
    fill_random(v_src, I2X(-5), I2X(5));
    fill_random(dens_src, I2X(-2), I2X(2));
}

void Int_NS_Grid::fluctuations() {
    fill_random(u_src, I2X(-4), I2X(4));
//    fill_random(v_src, -0.1, 0.1);
}
//-------------------------------------------------------------------------------------------------
void Int_NS_Grid::draw(QPainter & painter) {
    int width = 5, height = 5;
    int i, j, x, y;

    QColor color;
    freal min = min_dens();
    freal max = max_dens();
    freal factor = XD((max - min), I2X(255));

    int degree;

    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++) {
            y = width * i;
            x = height * j;

            if (factor != I2X(0))
                degree = X2I( XD((density(i, j) - min), factor) );
            else
                degree = 0;

//            color = w_black(degree);
            color = w_yellow(degree);

            painter.fillRect(x, y, width, height, QBrush(color));
        }
}

QColor Int_NS_Grid::w_black(const int degree) const {
    int icolor = 255 - degree;
    return QColor(icolor, icolor, icolor);
}

QColor Int_NS_Grid::w_yellow(const int degree) const {
    if (degree < 6)
        return QColor(Qt::white);
    if (degree > 250)
        return QColor(210, 140, 20, degree);
    return QColor(200, 140, 0, degree);
}

} // namespace Core
