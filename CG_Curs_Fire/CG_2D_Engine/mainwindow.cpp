#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <time.h>

typedef struct timespec Time;

Time get_Time() {
    Time gettime_now;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, & gettime_now);
    return gettime_now;
}

double get_End_Time(Time start_time) {
    Time end_time = get_Time();
    double sec = double(end_time.tv_sec - start_time.tv_sec) * 1000;
    double nsec = double(end_time.tv_nsec - start_time.tv_nsec) / 1000000;
    return sec + nsec;
}
//-------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    N = 60;
    solver = new NS_Solver(N, 0.125, 0.015, 0.1);
    grid = new NS_Grid(N);

    ui->setupUi(this);
    connect(ui->simulate, SIGNAL(pressed()), SLOT(start_simulation()));

    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent * event) {
    if (event->timerId() == sim_timer) {

        // Time time = get_Time();
        solver->solver_step(N, *grid);
        this->update();
        // qDebug() << get_End_Time(time);

    }
}

//-------------------------------------------------------------------------------------------------
void MainWindow::start_simulation() {
    sim_timer = startTimer(50);
    grid->set_src();
    this->update();
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.translate(ui->view->pos());
    painter.fillRect(ui->view->rect(), QBrush(Qt::white));
    painter.setClipRect(ui->view->rect());

    paintGrid(painter);
}

void MainWindow::paintGrid(QPainter & painter) {
    int width = 5, height = 5;
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
