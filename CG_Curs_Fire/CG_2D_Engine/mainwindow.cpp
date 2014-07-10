#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    simulating(true)
{
    N = 100;
    solver = new NS_Solver(N, 0.125, 0.015, 0.1);
    grid = new NS_Grid(N);

    ui->setupUi(this);
    connect(ui->simulate, SIGNAL(pressed()), SLOT(simulate()));

    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow() {
    delete ui;
}

//-------------------------------------------------------------------------------------------------
void MainWindow::simulate() {
    solver->solver_step(N, *grid);
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
    float min_dens = grid->min_dens();
    float max_dens = grid->max_dens();
    float factor = (max_dens - min_dens) / 255;

    int icolor;

    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++) {
            x = width * i;
            y = height * j;
            //painter.drawRect(x, y, width, height);

            icolor = 255 - qRound( (grid->density(i, j) - min_dens) / factor );
            color = QColor(icolor, icolor, icolor);

            painter.fillRect(x, y, width, height, QBrush(color));
            //painter.fillRect(x + 1, y + 1, width - 1, height - 1, QBrush(color));

            //painter.drawText(x + 5, y + height / 2, QString::number(dens[IX(i,j)]));
        }
}
