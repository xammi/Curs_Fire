#ifndef SCENE_H
#define SCENE_H

#include "Geometry/Obstacle.h"

//-------------------------------------------------------------------------------------------------
class Scene : public QObject
{
    Q_OBJECT

    typedef QVector<Drawable *> Draws;

signals:
    void throwException(Exception &);
    void throwMessage(QString);

public:
    explicit Scene(QObject * parent = 0);
    ~Scene();

    void setScreen(const QSize &);
    void setDefault();
    void draw(QPainter &) const;

private:
    Draws draws;
    Point3D center;
    Point3D cameraPos;

    QSize screen;
};

//-------------------------------------------------------------------------------------------------
#endif // SCENE_H
