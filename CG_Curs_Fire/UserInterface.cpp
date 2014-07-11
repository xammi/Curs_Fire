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
}

void UserInterface::adjustUi() {
    connect(scene, SIGNAL(throwException(Exception&)), this, SLOT(showException(Exception &)));
    connect(scene, SIGNAL(throwMessage(QString)), this, SLOT(showMessage(QString)));
}

UserInterface::~UserInterface() {
    delete ui;
}
//-------------------------------------------------------------------------------------------------
void UserInterface::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.translate(ui->view->pos());
    painter.fillRect(ui->view->rect(), QBrush(Qt::white));
    painter.setClipRect(ui->view->rect());

    scene->setScreen(ui->view->size());
}

void UserInterface::keyPressEvent(QKeyEvent *) {
}
//-------------------------------------------------------------------------------------------------
void UserInterface::showException(Exception & exc) {
    ui->overlay->setText(exc.toString());
}

void UserInterface::showMessage(QString msg) {
    ui->overlay->setText(msg);
}
