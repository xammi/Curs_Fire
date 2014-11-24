#include "UserInterface.h"
#include "ui_UserInterface.h"

//-------------------------------------------------------------------------------------------------
UserInterface::UserInterface(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::UserInterface),
    scene(new Scene(this))
{
    ui->setupUi(this);
    scene->setDefault();
    animeTimer = startTimer(50);

    sliders = { ui->reg_visc, ui->reg_diff, ui->reg_dt, ui->reg_dens_src,
                ui->reg_v_up, ui->reg_v_side, ui->reg_v_flucts, ui->reg_u_flucts };
    flames = { ui->rbn_flame1 };
    smokes = { ui->rbn_smoke1 };

    this->adjustUi();
    scene->restoreAdjusts();
}

void UserInterface::adjustUi() {
    connect(scene, SIGNAL(throwException(Exception&)), this, SLOT(showException(Exception &)));
    connect(scene, SIGNAL(throwMessage(QString)), this, SLOT(showMessage(QString)));

    for (QSlider * slider : sliders) {
        connect(slider, SIGNAL(valueChanged(int)), scene, SLOT(paramChanged(int)));
    }

    connect(scene, SIGNAL(updateParams(const QVector<int> &)), SLOT(updateParams(const QVector<int> &)));

    for (QRadioButton * rbn : flames + smokes) {
        connect(rbn, SIGNAL(pressed()), scene, SLOT(setParamReciever()));
    }

    connect(ui->btn_save, SIGNAL(pressed()), scene, SLOT(saveAdjusts()));
    connect(ui->btn_restore, SIGNAL(pressed()), scene, SLOT(restoreAdjusts()));

    this->setWindowState(Qt::WindowMaximized);
    flames[0]->setChecked(true);
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

    painter.setRenderHint(QPainter::Antialiasing, true);

    scene->setScreen(ui->view->size());
    scene->draw(painter);
}

void UserInterface::keyPressEvent(QKeyEvent * event) {
    switch (event->key()) {
        case Qt::Key_A: scene->cameraMotion(Camera::LEFT);
        break;
        case Qt::Key_D: scene->cameraMotion(Camera::RIGHT);
        break;
        case Qt::Key_W: scene->cameraMotion(Camera::UP);
        break;
        case Qt::Key_S: scene->cameraMotion(Camera::DOWN);
        break;
        case Qt::Key_X: scene->cameraMotion(Camera::TOWARD);
        break;
        case Qt::Key_Z: scene->cameraMotion(Camera::BACK);
        break;
        case Qt::Key_Q: scene->specialKey();
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

void UserInterface::updateParams(const QVector<int> &params) {
    for (int I = 0; I < sliders.size(); ++I) {
        sliders[I]->setValue(params[I]);
    }
}
