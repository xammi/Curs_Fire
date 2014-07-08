#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    simulating(true),
    N(100),
    solver(100, 0.125, 0.015, 0.1)
{
    set_conf();
    set_velocity_src();
    set_density_src();

    ui->setupUi(this);
    connect(ui->simulate, SIGNAL(pressed()), SLOT(simulate()));

    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow() {
    delete ui;
    dispose_conf();
}

void MainWindow::dispose_conf() {
    if (u) delete [] u;
    if (v) delete [] v;
    if (dens) delete [] dens;

    if (u_prev) delete [] u_prev;
    if (v_prev) delete [] v_prev;
    if (dens_prev) delete [] dens_prev;
}

void MainWindow::set_conf() {
    int size = (N+2) * (N+2);

    u = new float[size];
    v = new float[size];
    dens = new float[size];

    u_prev = new float[size];
    v_prev = new float[size];
    dens_prev = new float[size];
}

//-------------------------------------------------------------------------------------------------
void MainWindow::set_density_src() {
    dens_prev[IX(5,5)] = 1;
    dens_prev[IX(15, 12)] = -0.5;
    dens_prev[IX(22,34)] = 3;
    dens_prev[IX(25,30)] = -1;
}

void MainWindow::set_velocity_src() {
    u_prev[IX(3,2)] = 0.1;
    u_prev[IX(8,4)] = 0.1;
    v_prev[IX(12,15)] = 0.2;
}

void MainWindow::simulate() {
    solver.solver_step(N, dens, dens_prev, u, v, u_prev, v_prev);
    this->update();
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.translate(ui->view->pos());
    painter.fillRect(ui->view->rect(), QBrush(Qt::white));
    painter.setClipRect(ui->view->rect());

    int width = 2, height = 2;
    int i, j, x, y;

    QColor color;
    float min_dens, max_dens;
    min_dens = solver.get_min(dens);
    max_dens = solver.get_max(dens);
    float factor = (max_dens - min_dens) / 255;

    int icolor;

    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++) {
            x = width * i;
            y = height * j;
            //painter.drawRect(x, y, width, height);

            icolor = 255 - qRound( (dens[IX(i,j)] - min_dens) / factor );
            color = QColor(icolor, icolor, icolor);

            painter.fillRect(x, y, width, height, QBrush(color));
            //painter.fillRect(x + 1, y + 1, width - 1, height - 1, QBrush(color));

            //painter.drawText(x + 5, y + height / 2, QString::number(dens[IX(i,j)]));
        }
}
