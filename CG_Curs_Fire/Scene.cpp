#include "Scene.h"

#include "Geometry/Obstacle.h"
#include "Animetry/Flame.h"
#include "Animetry/Smoke.h"

const float SINGLE_CAM_ANGLE = 0.05;
const float CAM_ZOOM = 1.01;
//-------------------------------------------------------------------------------------------------
Scene::Scene(QObject * parent) :
    QObject(parent)
{
    int userZ = 1000;
    cameraPos = Point3D(0, 0, userZ);
    cameraX = Point3D(1, 0, userZ);
    cameraY = Point3D(0, 1, userZ);

    center = Point3D(0, 0, 0);
    scale = 1;
}

Scene::~Scene() {
    for (Drawable * draw : draws)
        if (draw) delete draw;
}

//-------------------------------------------------------------------------------------------------
void Scene::setScreen(const QSize & screen) {
    this->screen = screen;
}

void Scene::setDefault() {
    draws.append(new Obstacle(-100, 100, -100, 100, -100, 100, Matter::WOOD));
    draws.append(new Obstacle(-400, -200, -400, -200, -400, -300, Matter::STONE));
    draws.append(new Flame(-200, -100, -200, -100, -200, -100));
}

void Scene::draw(QPainter & painter) {
    Plane3D plane = Plane3D(cameraPos, cameraPos - center);
    Vector3D singleX = (cameraX - cameraPos) * scale,
             singleY = (cameraY - cameraPos) * scale;

    auto projector = [ & ] (const Point3D & point)->QPoint {
        Point3D proj = plane.project(point);
        Vector3D V = proj - cameraPos;
        return QPoint(destructBy(V, singleX), destructBy(V, singleY));
    };

    sortDraws(plane);
    for (Drawable * drawable : draws)
        drawable->draw(painter, projector, plane);
}

void Scene::cameraMotion(const Camera camera) {
    switch (camera) {
        case Camera::LEFT: cameraLeftRight(-SINGLE_CAM_ANGLE);
        break;
        case Camera::RIGHT: cameraLeftRight(SINGLE_CAM_ANGLE);
        break;
        case Camera::UP: cameraUpDown(-SINGLE_CAM_ANGLE);
        break;
        case Camera::DOWN: cameraUpDown(SINGLE_CAM_ANGLE);
        break;
        case Camera::TOWARD: cameraTowardBack(CAM_ZOOM);
        break;
        case Camera::BACK: cameraTowardBack(1./CAM_ZOOM);
        break;
    }
}

void Scene::cameraLeftRight(float angle) {
    cameraPos = rotate_XZ(cameraPos, center, angle);
    cameraX = rotate_XZ(cameraX, center, angle);
    cameraY = rotate_XZ(cameraY, center, angle);
}

void Scene::cameraUpDown(float angle) {
    cameraPos = rotate_YZ(cameraPos, center, angle);
    cameraX = rotate_YZ(cameraX, center, angle);
    cameraY = rotate_YZ(cameraY, center, angle);
}

void Scene::cameraTowardBack(float zoom) {
    scale *= zoom;
}
//-------------------------------------------------------------------------------------------------
void Scene::sortDraws(const Plane3D & plane) {

    QList<DrawDist> dists;
    for (Drawable * draw : draws) {
        double dist = plane.dist(draw->center());
        dists.append(DrawDist(draw, dist));
    }

    qSort(dists.begin(), dists.end(),
          [] (DrawDist & A, DrawDist & B) { return A.second < B.second; }
    );

    for (int I = 0; I < dists.size(); ++I)
        draws[I] = dists[I].first;
}

void Scene::updateAnime() {
    for (Drawable * drawable : draws)
        drawable->updateByTimer();
}
