#include "Flame.h"

//-------------------------------------------------------------------------------------------------

void Flame::initialize() {
    this->N = 60;
    this->solver = new NS_Solver(N, 0.01, 0.0002, 0.1);
    this->grid = new NS_Grid(N);
}

Flame::Flame() :
    Drawable()
{
    this->initialize();
}

Flame::Flame(double lX, double rX, double lY, double rY, double lZ, double rZ)  :
    Drawable(lX, rX, lY,rY, lZ, rZ)
{
    this->initialize();
}

Flame::~Flame() {
    if (solver) delete solver;
    if (grid) delete grid;
}
//-------------------------------------------------------------------------------------------------
void Flame::draw(QPainter & painter, const Projector & projector, const Plane3D & plane) {
    int width = 5, height = 5;
    int i, j, x, y;

    QColor color;
    float min = grid->min_dens();
    float max = grid->max_dens();

    if (max - min == 0)
        return;

    float factor = 255 / (max - min);

    int degree;

    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++) {
            y = width * i;
            x = height * j;

            degree = qRound( (grid->density(i, j) - min) * factor );
            color = w_yellow(degree);

            painter.fillRect(x, y, width, height, QBrush(color));
        }
}


void Flame::updateByTimer() {
    solver->solver_step(N, *grid);
    grid->fluctuations();
}


QColor Flame::w_yellow(const int degree) const {
    if (degree < 6)
        return QColor(Qt::white);
    if (degree > 250)
        return QColor(210, 140, 20, degree);
    return QColor(200, 140, 0, degree);
}
