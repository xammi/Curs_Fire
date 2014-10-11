#ifndef SCENE_H
#define SCENE_H

#include "Geometry/Drawable.h"
#include "Animetry/Adjustable.h"
#include "Task.h"

//-------------------------------------------------------------------------------------------------
enum class Camera { LEFT = 0, RIGHT, UP, DOWN, TOWARD, BACK };

class Scene : public QObject
{
    Q_OBJECT

    typedef QVector<Drawable *> Draws;
    typedef QVector<Adjustable *> Adjusts;
    typedef std::pair<Drawable *, double> DrawDist;

signals:
    void throwException(Exception &);
    void throwMessage(QString);
    void updateParams(const QVector<int> &);

public slots:
    void setParamReciever();
    void paramChanged(int);
    void saveAdjusts();
    void restoreAdjusts();

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
    Adjusts adjusts;

    Point3D center;
    Point3D cameraPos, cameraX, cameraY;
    QSize screen;

    double scale;
    int paramReciever;
};

//-------------------------------------------------------------------------------------------------
#endif // SCENE_H
