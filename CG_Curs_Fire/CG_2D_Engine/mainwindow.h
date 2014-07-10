#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QThread>

#include "ns_solver.h"
#include "ns_grid.h"

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
    explicit MainWindow(QWidget * parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private:
    NS_Solver * solver;
    NS_Grid * grid;
    int N;

    Ui::MainWindow * ui;

    bool simulating;
};
//-------------------------------------------------------------------------------------------------
#endif // MAINWINDOW_H
