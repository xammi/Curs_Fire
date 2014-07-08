#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QThread>

#include "ns_solver.h"

using namespace Core;

//-------------------------------------------------------------------------------------------------
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void simulate();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private:
    void set_conf();
    void dispose_conf();

    void set_density_src();
    void set_velocity_src();

    NS_Solver solver;
    int N;

    float * u, * u_prev;
    float * v, * v_prev;
    float * dens, * dens_prev;

    Ui::MainWindow *ui;

    bool simulating;
};
//-------------------------------------------------------------------------------------------------
#endif // MAINWINDOW_H
