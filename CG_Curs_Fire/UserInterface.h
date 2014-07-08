#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Scene.h"

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
    class UserInterface;
}

//-------------------------------------------------------------------------------------------------
class UserInterface : public QMainWindow
{
    Q_OBJECT

private slots:
    void showException(Exception &);
    void showMessage(QString);

public:
    explicit UserInterface(QWidget * parent = 0);
    ~UserInterface();

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    void adjustUi();

    Ui::UserInterface * ui;
    Scene * scene;
};
//-------------------------------------------------------------------------------------------------

#endif // USERINTERFACE_H
