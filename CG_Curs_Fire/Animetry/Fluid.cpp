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
        //draw_XZ(painter, projector, lY, min, factor);
    }
    else if (type == SMOKE) {
        double midY = lY + (rY - lY) / 2;
        //draw_XZ(painter, projector, midY, min, factor);
    }
}

void Fluid::draw_ZY(QPainter & painter, const Projector & projector, double X, float min, float factor) {
    double stepY = (rY -lY) / N,
           stepZ = (rZ - lZ) / N;

    Polygon3D rect(Point3D(X, lY, lZ),
                   Vector3D(0, stepY, 0),
                   Vector3D(0, 0, stepZ));

    for (int I = 1; I < N; ++I) {
        for (int J = 1; J < N; ++J) {
            rect.shift_Y(stepY);

            int degree = qRound( (grid->density(I, J) - min) * factor );
            QColor color = grid->color(degree);
            painter.setBrush(QBrush(color));

            drawPolygon(rect, painter, projector);
        }
        rect.shift(Vector3D(0, - (N-1) * stepY, stepZ));
    }
}

void Fluid::draw_XY(QPainter & painter, const Projector & projector, double Z, float min, float factor) {
    double stepX = (rX - lX) / N,
           stepY = (rY -lY) / N;

    Polygon3D rect(Point3D(lX, lY, Z),
                   Vector3D(stepX, 0, 0),
                   Vector3D(0, stepY, 0));

    for (int I = 1; I < N; ++I) {
        for (int J = 1; J < N; ++J) {
            rect.shift_Y(stepY);

            int degree = qRound( (grid->density(I, J) - min) * factor );
            QColor color = grid->color(degree);
            painter.setBrush(QBrush(color));

            drawPolygon(rect, painter, projector);
        }
        rect.shift(Vector3D(stepX, - (N-1) * stepY, 0));
    }
}

void Fluid::draw_XZ(QPainter & painter, const Projector & projector, double Y, float min, float factor) {
    double stepX = (rX - lX) / N,
           stepZ = (rZ - lZ) / N;

    Polygon3D rect(Point3D(lX, Y, lZ),
                   Vector3D(stepX, 0, 0),
                   Vector3D(0, 0, stepZ));

    int N_2 = N / 2;

    for (int I = 1; I < N; ++I) {
        for (int J = 1; J < N; ++J) {
            rect.shift_Z(stepZ);

            double dI = grid->density(I, N_2),
                   dJ = grid->density(J, N_2),
                   dist_I = qPow(N_2 - I, 2) || 1,
                   dist_J = qPow(N_2 - J, 2) || 1,
                   dd = qPow(dI, 2) / dist_I + qPow(dJ, 2) / dist_J;

            int degree = qRound( (qSqrt(dd) - min) * factor );
            QColor color = grid->color(degree);
            painter.setBrush(QBrush(color));

            drawPolygon(rect, painter, projector);
        }
        rect.shift(Vector3D(stepX, 0, - (N-1) * stepZ));
    }
}

void Fluid::drawPolygon(const Polygon3D & polygon3D, QPainter & painter, const Projector & projector) {
    QPolygon polygon;
    polygon.resize(4);

    for (int I = 0; I < polygon3D.size(); I++)
        polygon[I] = projector(polygon3D[I]);

    painter.drawPolygon(polygon);
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
