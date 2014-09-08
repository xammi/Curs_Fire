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
    solver = new Int_NS_Solver(N, 0.01, 0.0002, 0.1);
    grid = new Int_NS_Grid(N);

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
        grid->fluctuations();
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

    grid->draw(painter);
}
