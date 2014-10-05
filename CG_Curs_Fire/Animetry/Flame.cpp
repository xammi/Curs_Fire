#include "Flame.h"

//-------------------------------------------------------------------------------------------------

void Flame::initialize() {
    this->N = 40;
    this->solver = new NS_Solver(N, 0.01, 0.0002, 0.1);
    this->grid = new FlameGrid(N);

    grid->set_density_src();
    grid->set_velocity_src();
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
void Flame::draw(QPainter & painter, const Projector & projector, const Plane3D &) {
    int i, j, degree;

    QColor color;
    float min = grid->min_dens();
    float max = grid->max_dens();

    if (max - min == 0)
        return;

    float factor = 255 / (max - min);

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
        for (double Y = lY; Y < rY - 10; Y += stepY, j++) {

            points = {Point3D(X, Y, Z),
                      Point3D(X, Y + stepY, Z),
                      Point3D(X, Y + stepY, Z + stepZ),
                      Point3D(X, Y, Z + stepZ) };

            degree = qRound( (grid->density(N - j, i) - min) * factor );
            color = w_yellow(degree);
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
        for (double Y = lY; Y < rY - 10; Y += stepY, j++) {

            points = { Point3D(X, Y, Z),
                       Point3D(X, Y + stepY, Z),
                       Point3D(X + stepX, Y + stepY, Z),
                       Point3D(X + stepX, Y, Z) };

            degree = qRound( (grid->density(N - j, i) - min) * factor );
            color = w_yellow(degree);
            painter.setBrush(QBrush(color));

            for (int k = 0; k < 4; k++)
                polygon[k] = projector(points[k]);
            painter.drawPolygon(polygon);
        }
    }
}

void Flame::run() {
    solver->solver_step(N, *grid);
    grid->fluctuations();
}

void Flame::updateByTimer() {
    this->setAutoDelete(false);
    QThreadPool::globalInstance()->start(this);
}

void Flame::specialAction() {
    grid->set_density_src();
    grid->set_velocity_src();
}


QColor Flame::w_yellow(const int degree) const {
    if (degree < 1)
        return QColor(255, 255, 255, 0);
    return QColor(200, 140, 0, degree);
}
//-------------------------------------------------------------------------------------------------
void FlameGrid::set_density_src() {
    float POSIT = 20;

    for (int I = N - 3; I <= N; I++)
        for (int J = 5; J <= N - 5; J++) {
            dens_src[IX(I, J)] = -POSIT;
        }
}

void FlameGrid::set_velocity_src() {
    float UP = -0.3;
    float DOWN = 3;

    for (int I = 0; I < 1; ++I)
        for (int J = 1; J < N/2; ++J) {
            v[IX(I,J)] = DOWN;
            v[IX(I,N-J)] = -DOWN;
        }

    for (int I = 10; I <= 15; I++)
        for (int J = 0; J <= 1; J++) {
            u[IX(I,J)] = DOWN;
            u[IX(I,N-J+1)] = DOWN;
        }

    for (int I = 10; I <= N; I++)
        for (int J = 2; J <= N - 1; J++) {
            u[IX(I,J)] = UP;
        }
}

void FlameGrid::fluctuations() {
    set_density_src();
    set_velocity_src();

    fill_random(u_src, -5., 5.);
    fill_random(v_src, -1., 1.);
}
