#include "Fluid.h"


void Fluid::initialize() {
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
    Drawable(), type(FLAME)
{
    this->initialize();
}

Fluid::Fluid(double lX, double rX, double lY, double rY, double lZ, double rZ, Type type)  :
    Drawable(lX, rX, lY,rY, lZ, rZ), type(type)
{
    this->initialize();
}

Fluid::~Fluid() {
    if (solver) delete solver;
    if (grid) delete grid;
}
//-------------------------------------------------------------------------------------------------
void Fluid::draw(QPainter & painter, const Projector & projector, const Plane3D &) {
    float min = grid->min_dens(),
          max = grid->max_dens();

    if (max - min == 0)
        return;

    float factor = 255 / (max - min);

    painter.setPen(QPen(Qt::white, 0, Qt::NoPen));

    double midZ = lZ + (rZ - lZ) / 2;
    draw_XY(painter, projector, midZ, min, factor);

    double midX = lX + (rX - lX) / 2;
    draw_ZY(painter, projector, midX, min, factor);

    if (type == FLAME) {
        draw_XZ(painter, projector, lY, min, factor);
    }
    else if (type == SMOKE) {
        double midY = lY + (rY - lY) / 2;
        draw_XZ(painter, projector, midY, min, factor);
    }
}

void Fluid::draw_ZY(QPainter & painter, const Projector & projector, double X, float min, float factor) {
    double stepY = (rY -lY) / N,
           stepZ = (rZ - lZ) / N;

    QPolygon polygon;
    polygon.resize(4);

    int i = 1, j;
    for (double Z = lZ; Z < rZ; Z += stepZ, i++) {
        j = 1;
        for (double Y = lY; Y < rY - 10; Y += stepY, j++) {
            Points3D points = { Point3D(X, Y, Z),
                                Point3D(X, Y + stepY, Z),
                                Point3D(X, Y + stepY, Z + stepZ),
                                Point3D(X, Y, Z + stepZ) };

            int degree = qRound( (grid->density(i, j) - min) * factor );
            QColor color = grid->color(degree);
            painter.setBrush(QBrush(color));

            for (int k = 0; k < 4; k++)
                polygon[k] = projector(points[k]);
            painter.drawPolygon(polygon);
        }
    }
}

void Fluid::draw_XY(QPainter & painter, const Projector & projector, double Z, float min, float factor) {
    double stepX = (rX - lX) / N,
           stepY = (rY -lY) / N;

    QPolygon polygon;
    polygon.resize(4);

    int i = 1, j;
    for (double X = lX; X < rX; X += stepX, i++) {
        j = 1;
        for (double Y = lY; Y < rY - 10; Y += stepY, j++) {
            Points3D points = { Point3D(X, Y, Z),
                                Point3D(X, Y + stepY, Z),
                                Point3D(X + stepX, Y + stepY, Z),
                                Point3D(X + stepX, Y, Z) };

            int degree = qRound( (grid->density(i, j) - min) * factor );
            QColor color = grid->color(degree);
            painter.setBrush(QBrush(color));

            for (int k = 0; k < 4; k++)
                polygon[k] = projector(points[k]);
            painter.drawPolygon(polygon);
        }
    }
}

void Fluid::draw_XZ(QPainter & painter, const Projector & projector, double Y, float min, float factor) {
    double stepX = (rX - lX) / N,
           stepZ = (rZ - lZ) / N;

    QPolygon polygon;
    polygon.resize(4);

    // TODO: i,j controlling
    int i = 1, j;

    for (double X = lX; X < rX; X += stepX, i++) {
        j = 1;
        for (double Z = lZ; Z < rZ; Z += stepZ) {
            Points3D points = { Point3D(X, Y, Z),
                                Point3D(X, Y, Z + stepZ),
                                Point3D(X + stepX, Y, Z + stepZ),
                                Point3D(X + stepX, Y, Z) };

            int degree = qRound( (grid->density(i, j) - min) * factor );
            QColor color = grid->color(degree);
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
