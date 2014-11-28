#include "Scene.h"

#include "Geometry/Obstacle.h"
#include "Animetry/Fluid.h"

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
    Fluid * centralFlame = new Fluid(-100, 100, -100, 100, -100, 100, Fluid::FLAME);
    Fluid * centralSmoke = new Fluid(-100, 100, 90, 290, -100, 100, Fluid::SMOKE);

    Obstacle * log_1 = new Obstacle(-100, 100, -140, -100, -20, 20, Obstacle::OAK);
    Obstacle * log_2 = new Obstacle(-20, 20, -140, -100, -100, 100, Obstacle::OAK);

    draws.append(centralFlame);
    draws.append(centralSmoke);
    draws.append(log_1);
    draws.append(log_2);

    adjusts.append(centralFlame);
    adjusts.append(centralSmoke);
    paramReciever = 0;
}

void Scene::draw(QPainter & painter) {
    Plane3D plane = Plane3D(cameraPos, cameraPos - center);
    Vector3D singleX = (cameraX - cameraPos) * scale,
             singleY = (cameraY - cameraPos) * scale;

    auto projector = [ plane, singleX, singleY, cameraPos ] (const Point3D & point)->QPoint {
        Point3D proj = plane.project(point);
        Vector3D V = proj - cameraPos;
        return QPoint(destructBy(V, singleX), destructBy(V, singleY));
    };

    sortDraws(plane);

//    auto callTask = [ & painter, projector, plane ] (Drawable * drawable) {
//        drawable->draw(painter, projector, plane);
//    };

//    QThreadPool * pool = QThreadPool::globalInstance();
    for (Drawable * drawable : draws)
//        pool->start(new Task(drawable, callTask));
        drawable->draw(painter, projector, plane);
//    pool->waitForDone();
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
          [] (DrawDist & A, DrawDist & B) { return A.second > B.second; }
    );

    for (int I = 0; I < dists.size(); ++I)
        draws[I] = dists[I].first;    
}

void Scene::updateAnime() {
//    auto taskCall = [] (Drawable * drawable) {
//        drawable->updateByTimer();
//    };

//    QThreadPool * pool = QThreadPool::globalInstance();
    for (Drawable * drawable : draws)
        drawable->updateByTimer();
//        pool->start(new Task(drawable, taskCall));

//    pool->waitForDone();
}

void Scene::specialKey() {
    for (Drawable * drawable : draws)
        drawable->specialAction();
}
//-------------------------------------------------------------------------------------------------
void Scene::setParamReciever() {
    QString rbn = sender()->objectName();
    rbn = rbn.remove(0, rbn.indexOf('_') + 1);

    if (rbn == "flame1")
        this->paramReciever = 0;
    else if (rbn == "smoke1")
        this->paramReciever = 1;

    emit updateParams(adjusts[paramReciever]->getParams());
}

void Scene::paramChanged(int value) {
    QString reg = sender()->objectName();
    reg = reg.remove(0, reg.indexOf('_') + 1);

    adjusts[paramReciever]->setParam(reg, value);
}

void Scene::saveAdjusts() {
    adjusts[paramReciever]->save();
}
void Scene::restoreAdjusts() {
    adjusts[paramReciever]->restore();
    emit updateParams(adjusts[paramReciever]->getParams());
}
