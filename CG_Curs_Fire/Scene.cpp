#include "Scene.h"

//-------------------------------------------------------------------------------------------------
Scene::Scene(QObject * parent) :
    QObject(parent)
{}
//-------------------------------------------------------------------------------------------------
void Scene::setScreen(const QSize & screen) {
    this->screen = screen;
}
