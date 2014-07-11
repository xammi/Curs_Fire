#include "Scene.h"

//-------------------------------------------------------------------------------------------------
Scene::Scene(QObject * parent) :
    QObject(parent)
{}

Scene::~Scene() {
    for (Drawable * draw : draws)
        if (draw) delete draw;
}

//-------------------------------------------------------------------------------------------------
void Scene::setScreen(const QSize & screen) {
    this->screen = screen;
}

void Scene::setDefault() {
    draws.append(new Obstacle(-10, 10, -10, 10, -10, 10, Matter::WOOD));
    draws.append(new Obstacle(-40, -20, -40, -20, -40, -30));
}

void Scene::draw(QPainter & painter) const {
    auto projector = [] (const Point3D & point)->QPoint {
        return QPoint(point.X, point.Y);
    };

    for (Drawable * draw : draws)
        draw->draw(painter, projector);
}
