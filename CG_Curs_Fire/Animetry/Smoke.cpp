#include "Smoke.h"

//-------------------------------------------------------------------------------------------------

void Smoke::initialize() {
    this->N = 60;
    this->solver = new NS_Solver(N, 0.01, 0.0002, 0.1);
    this->grid = new NS_Grid(N);
}

Smoke::Smoke() :
    Drawable()
{
    this->initialize();
}

Smoke::Smoke(double lX, double rX, double lY, double rY, double lZ, double rZ) :
    Drawable(lX, rX, lY,rY, lZ, rZ)
{
    this->initialize();
}

Smoke::~Smoke() {
    if (solver) delete solver;
    if (grid) delete grid;
}
//-------------------------------------------------------------------------------------------------
void Smoke::draw(QPainter & painter, const Projector & projector, const Plane3D & plane) {

}

void Smoke::updateByTimer() {
    solver->solver_step(N, *grid);
    grid->fluctuations();
}

QColor Smoke::w_black(const int degree) const {
    int icolor = 255 - degree;
    return QColor(icolor, icolor, icolor);
}
