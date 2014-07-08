#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "includes.h"
#include "Point3d.h"

//-------------------------------------------------------------------------------------------------

class Drawable {
public:
    Drawable();
    virtual ~Drawable() {}

    virtual void draw(QPainter &) = 0;

    Point3D center() const;

protected:
    double lX, rX;
    double lY, rY;
    double lZ, rZ;
};

//-------------------------------------------------------------------------------------------------

#endif // DRAWABLE_H
