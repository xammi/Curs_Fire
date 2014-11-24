#include "Fluid.h"


void Fluid::initialize(const Type type) {
    this->N = GEN_N;

    if (type == FLAME)
        this->grid = new FlameGrid(N);
    else if (type == SMOKE)
        this->grid = new SmokeGrid(N);

    this->solver = new NS_Solver(N, transVal(0.01, 0.5, visc),
                                 transVal(0.001, 0.01, diff),
                                 transVal(0.005, 0.025, dt));

    grid->set_density_src(dens_src_power);
    grid->set_velocity_src(v_up, v_side);
}

Fluid::Fluid() :
    Drawable()
{
    this->initialize(FLAME);
}

Fluid::Fluid(double lX, double rX, double lY, double rY, double lZ, double rZ, Type type)  :
    Drawable(lX, rX, lY,rY, lZ, rZ)
{
    this->initialize(type);
}

Fluid::~Fluid() {
    if (solver) delete solver;
    if (grid) delete grid;
}
//-------------------------------------------------------------------------------------------------
void Fluid::draw(QPainter & painter, const Projector & projector, const Plane3D &) {
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

            degree = qRound( (grid->density(i, j) - min) * factor );
            color = grid->color(degree);
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

            degree = qRound( (grid->density(i, j) - min) * factor );
            color = grid->color(degree);
            painter.setBrush(QBrush(color));

            for (int k = 0; k < 4; k++)
                polygon[k] = projector(points[k]);
            painter.drawPolygon(polygon);
        }
    }
}

void Fluid::updateByTimer() {
    solver->solver_step(N, *grid);

    grid->set_density_src(dens_src_power);
    grid->set_velocity_src(v_up, v_side);
    grid->fluctuations(v_flucts, u_flucts);
}

void Fluid::specialAction() {
    grid->to_zero();
}

void Fluid::withSet() {
    solver->set_params(transVal(0.01, 0.5, visc),
                       transVal(0.001, 0.01, diff),
                       transVal(0.005, 0.025, dt));
}
