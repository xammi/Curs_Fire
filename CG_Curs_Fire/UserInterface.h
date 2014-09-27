#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Scene.h"

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimerEvent>

namespace Ui {
    class UserInterface;
}

//-------------------------------------------------------------------------------------------------
class UserInterface : public QMainWindow
{
    Q_OBJECT

    typedef int Timer;

private slots:
    void showException(Exception &);
    void showMessage(QString);

public:
    explicit UserInterface(QWidget * parent = 0);
    ~UserInterface();

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);

private:
    void adjustUi();

    Ui::UserInterface * ui;
    Scene * scene;
    Timer animeTimer;
};
//-------------------------------------------------------------------------------------------------

#endif // USERINTERFACE_H
