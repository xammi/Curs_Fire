#include "int_grid.h"
#include "time.h"

namespace Core {

//-------------------------------------------------------------------------------------------------
Int_NS_Grid::Int_NS_Grid(const int _N) :
    N(_N)
{
    uint T = time(NULL);
    qsrand(T);

    size = (N+2) * (N+2);
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
    u = new float[size];
    v = new float[size];
    dens = new float[size];

    u_src = new float[size];
    v_src = new float[size];
    dens_src = new float[size];

    if (!u || !v || !dens || !u_src || !v_src || !dens_src)
        throw MemNotAlloc();
}

float Int_NS_Grid::density(int i, int j) const {
    return dens[IX(i, j)];
}

float Int_NS_Grid::min_dens() const {
    return get_min(size, dens);
}

float Int_NS_Grid::max_dens() const {
    return get_max(size, dens);
}

//-------------------------------------------------------------------------------------------------
void Int_NS_Grid::set_src() {
    set_density_src();
    set_velocity_src();
//    set_random_src();
}

void Int_NS_Grid::set_density_src() {
    float POSIT = 50;
    float NEGAT_SIDE = 0;
    float NEGAT_TOP = 0;

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
    float UP = -10;

    for (int I = 1; I <= N; I++)
        for (int J = 1; J <= N; J++) {
            u_src[IX(I,J)] = UP;
        }
}

void Int_NS_Grid::set_random_src() {
    fill_random(size, u_src, -5, 5);
    fill_random(size, v_src, -5, 5);
    fill_random(size, dens_src, -2, 2);
}

void Int_NS_Grid::fluctuations() {
    fill_random(size, u_src, -4, 4);
//    fill_random(size, v_src, -0.1, 0.1);
}
//-------------------------------------------------------------------------------------------------
void Int_NS_Grid::draw(QPainter & painter) {
    int width = 5, height = 5;
    int i, j, x, y;

    QColor color;
    float min = min_dens();
    float max = max_dens();
    float factor = (max - min) / 255;

    int degree;

    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++) {
            y = width * i;
            x = height * j;

            degree = qRound( (density(i, j) - min) / factor );
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
