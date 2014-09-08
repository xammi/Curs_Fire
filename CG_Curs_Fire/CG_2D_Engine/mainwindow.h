#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QThread>

#include "usual/ns_solver.h"
#include "integral/int_solver.h"

using namespace Core;

//-------------------------------------------------------------------------------------------------
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void start_simulation();

public:
    explicit MainWindow(QWidget * parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

private:
    Int_NS_Solver * solver;
    Int_NS_Grid * grid;
    int N;

    Ui::MainWindow * ui;
    int sim_timer;
};
//-------------------------------------------------------------------------------------------------
#endif // MAINWINDOW_H
