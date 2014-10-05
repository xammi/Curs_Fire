#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Prims3d.h"

//-------------------------------------------------------------------------------------------------
typedef std::function<QPoint (const Point3D &)> Projector;

class Drawable : public QObject
{
public:
    Drawable();
    Drawable(double lX, double rX, double lY, double rY, double lZ, double rZ);
    virtual ~Drawable() {}

    virtual void draw(QPainter &, const Projector &, const Plane3D &) = 0;
    virtual void updateByTimer() {}
    virtual void specialAction() {}

    Point3D center() const;
    bool isOwner(const Point3D &) const;

protected:
    double lX, rX;
    double lY, rY;
    double lZ, rZ;
};
//-------------------------------------------------------------------------------------------------

#endif // DRAWABLE_H
