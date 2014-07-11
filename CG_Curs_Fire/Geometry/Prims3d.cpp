#include "Prims3d.h"

Point3D::Point3D() :
    X(0), Y(0), Z(0)
{}

Point3D::Point3D(double _X, double _Y, double _Z) :
    X(_X), Y(_Y), Z(_Z)
{}
//-------------------------------------------------------------------------------------------------
Vector3D::Vector3D() :
    X(0), Y(0), Z(0)
{}

Vector3D::Vector3D(double _X, double _Y, double _Z) :
    X(_X), Y(_Y), Z(_Z)
{}

double Vector3D::abs(const Vector3D & vector) {
    return vector.X * vector.X + vector.Y * vector.Y + vector.Z * vector.Z;
}
//-------------------------------------------------------------------------------------------------
Point3D operator+(const Point3D & point,const Vector3D & direct) {
    return Point3D(point.X + direct.X,
                   point.Y + direct.Y,
                   point.Z + direct.Z);
}

Point3D operator -(const Point3D & point, const Vector3D & direct) {
    return Point3D(point.X - direct.X,
                   point.Y - direct.Y,
                   point.Z - direct.Z);
}

Vector3D operator-(const Point3D & erste, const Point3D & zweite) {
    return Vector3D(erste.X - zweite.X,
                    erste.Y - zweite.Y,
                    erste.Z - zweite.Z);
}
