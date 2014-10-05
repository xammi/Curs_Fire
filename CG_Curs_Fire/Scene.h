#ifndef SCENE_H
#define SCENE_H

#include "Geometry/Drawable.h"

//-------------------------------------------------------------------------------------------------
enum class Camera { LEFT = 0, RIGHT, UP, DOWN, TOWARD, BACK };

class Scene : public QObject
{
    Q_OBJECT

    typedef QVector<Drawable *> Draws;
    typedef std::pair<Drawable *, double> DrawDist;

signals:
    void throwException(Exception &);
    void throwMessage(QString);

public:
    explicit Scene(QObject * parent = 0);
    ~Scene();

    void setScreen(const QSize &);
    void setDefault();
    void draw(QPainter &);
    void cameraMotion(const Camera);
    void updateAnime();
    void specialKey();

private:
    void sortDraws(const Plane3D &);

    void cameraLeftRight(float angle);
    void cameraUpDown(float angle);
    void cameraTowardBack(float move);

private:
    Draws draws;
    Point3D center;
    Point3D cameraPos, cameraX, cameraY;
    QSize screen;

    double scale;
};

//-------------------------------------------------------------------------------------------------
#endif // SCENE_H
