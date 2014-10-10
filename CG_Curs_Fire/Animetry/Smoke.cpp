#include "Smoke.h"

//-------------------------------------------------------------------------------------------------

void Smoke::initialize() {
    this->N = GEN_N;
    this->solver = new NS_Solver(N, 0.0001, 0.002, 0.1);
    this->grid = new SmokeGrid(N);

    grid->set_density_src();
    grid->set_velocity_src();
}

Smoke::Smoke() :
    Drawable()
{
    this->initialize();
}

Smoke::Smoke(double lX, double rX, double lY, double rY, double lZ, double rZ, Flame * flame) :
    Drawable(lX, rX, lY,rY, lZ, rZ)
{
    this->flame = flame;
    this->initialize();
}

Smoke::~Smoke() {
    if (solver) delete solver;
    if (grid) delete grid;
}
//-------------------------------------------------------------------------------------------------
void Smoke::draw(QPainter & painter, const Projector & projector, const Plane3D &) {
    int i, j, degree;

    QColor color;
    FVal min = grid->min_dens();
    FVal max = grid->max_dens();

    if (max - min == 0)
        return;

    Factor factor = 255 / (max - min);

    double stepX = (rX - lX) / N,
           stepY = (rY -lY) / N,
           stepZ = (rZ - lZ) / N;


    painter.setPen(QPen(Qt::white, 0, Qt::NoPen));
    Points3D points;
    QPolygon polygon;
    polygon.resize(4);

    i = 0;
    double X = lX + (rX - lX) / 2;
    for (double Z = lZ; Z < rZ; Z += stepZ, i++) {
        j = 0;
        for (double Y = lY; Y < rY; Y += stepY, j++) {

            points = {Point3D(X, Y, Z),
                      Point3D(X, Y + stepY, Z),
                      Point3D(X, Y + stepY, Z + stepZ),
                      Point3D(X, Y, Z + stepZ) };

            degree = qRound( (grid->density(i, j) - min) * factor );
            color = w_black(degree);
            painter.setBrush(QBrush(color));

            for (int k = 0; k < 4; k++)
                polygon[k] = projector(points[k]);
            painter.drawPolygon(polygon);
        }
    }

    i = 0;
    double Z = lZ + (rZ - lZ) / 2;
    for (double X = lX; X < rX; X += stepX, i++) {
        j = 0;
        for (double Y = lY; Y < rY; Y += stepY, j++) {

            points = { Point3D(X, Y, Z),
                       Point3D(X, Y + stepY, Z),
                       Point3D(X + stepX, Y + stepY, Z),
                       Point3D(X + stepX, Y, Z) };

            degree = qRound( (grid->density(i, j) - min) * factor );
            color = w_black(degree);
            painter.setBrush(QBrush(color));

            for (int k = 0; k < 4; k++)
                polygon[k] = projector(points[k]);
            painter.drawPolygon(polygon);
        }
    }
}

void Smoke::run() {
    solver->solver_step(N, *grid);
    grid->fluctuations();
}

void Smoke::updateByTimer() {
    this->setAutoDelete(false);
    QThreadPool::globalInstance()->start(this);
}

void Smoke::specialAction() {
    grid->set_density_src();
    grid->set_velocity_src();
}

QColor Smoke::w_black(const int degree) const {
    if (degree < 1 || degree > 255)
        return QColor(255, 255, 255, 0);
    int icolor = degree;
    return QColor(icolor, icolor, icolor, icolor);
}

//-------------------------------------------------------------------------------------------------
void SmokeGrid::set_density_src() {
}

void SmokeGrid::set_velocity_src() {
}

void SmokeGrid::fluctuations() {
}
