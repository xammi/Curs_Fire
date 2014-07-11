#include "Drawable.h"

//-------------------------------------------------------------------------------------------------
Drawable::Drawable() :
    lX(0), rX(0), lY(0), rY(0), lZ(0), rZ(0)
{}

Drawable::Drawable(double _lX, double _rX, double _lY, double _rY, double _lZ, double _rZ) :
    lX(_lX), rX(_rX), lY(_lY), rY(_rY), lZ(_lZ), rZ(_rZ)
{}

//-------------------------------------------------------------------------------------------------
Point3D Drawable::center() const {
    double X = lX + (rX - lX) / 2,
           Y = lY + (rY - lY) / 2,
           Z = lZ + (rZ - lZ) / 2;
    return Point3D(X, Y, Z);
}

bool Drawable::isOwner(const Point3D & point) const {
    double X = point.X,
           Y = point.Y,
           Z = point.Z;

    if (X < lX || X > rX || Y < lY || Y > rY || Z < lZ || Z > rZ)
        return false;
    return true;
}
