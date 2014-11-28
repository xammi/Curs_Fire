#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Scene.h"

#include <QSlider>
#include <QRadioButton>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QPixmap>
#include <QGraphicsBlurEffect>

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
    void updateParams(const QVector<int> & params);

public:
    explicit UserInterface(QWidget * parent = 0);
    ~UserInterface();

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);

private:
    void adjustUi();
    void setEffects();

    QImage pixmap;
    Ui::UserInterface * ui;    
    Scene * scene;
    Timer animeTimer;

    QVector<QSlider *> sliders;
    QVector<QRadioButton *> flames;
    QVector<QRadioButton *> smokes;
};
//-------------------------------------------------------------------------------------------------

#endif // USERINTERFACE_H
