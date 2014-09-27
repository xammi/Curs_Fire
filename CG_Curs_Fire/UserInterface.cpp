#include "UserInterface.h"
#include "ui_UserInterface.h"

//-------------------------------------------------------------------------------------------------
UserInterface::UserInterface(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::UserInterface),
    scene(new Scene(this))
{
    ui->setupUi(this);
    this->adjustUi();
    scene->setDefault();
    animeTimer = startTimer(45);
}

void UserInterface::adjustUi() {
    connect(scene, SIGNAL(throwException(Exception&)), this, SLOT(showException(Exception &)));
    connect(scene, SIGNAL(throwMessage(QString)), this, SLOT(showMessage(QString)));
}

UserInterface::~UserInterface() {
    delete ui;
}
//-------------------------------------------------------------------------------------------------
void UserInterface::timerEvent(QTimerEvent * event) {
    if (event->timerId() == animeTimer) {
        scene->updateAnime();
        this->update();
    }
}

void UserInterface::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.translate(ui->view->pos());
    painter.fillRect(ui->view->rect(), QBrush(Qt::white));
    painter.setClipRect(ui->view->rect());

    painter.translate(ui->view->width() / 2, ui->view->height() / 2);
    painter.scale(1, -1);

    scene->setScreen(ui->view->size());
    scene->draw(painter);
}

void UserInterface::keyPressEvent(QKeyEvent * event) {
    switch (event->key()) {
        case Qt::Key_Left: scene->cameraMotion(Camera::LEFT);
        break;
        case Qt::Key_Right: scene->cameraMotion(Camera::RIGHT);
        break;
        case Qt::Key_Up: scene->cameraMotion(Camera::UP);
        break;
        case Qt::Key_Down: scene->cameraMotion(Camera::DOWN);
        break;
        case Qt::Key_Equal: scene->cameraMotion(Camera::TOWARD);
        break;
        case Qt::Key_Minus: scene->cameraMotion(Camera::BACK);
        break;
    }
    this->update();
}
//-------------------------------------------------------------------------------------------------
void UserInterface::showException(Exception & exc) {
    ui->overlay->setText(exc.toString());
}

void UserInterface::showMessage(QString msg) {
    ui->overlay->setText(msg);
}
