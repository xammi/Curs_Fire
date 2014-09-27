#ifndef POINT3D_H
#define POINT3D_H

#include "includes.h"

//-------------------------------------------------------------------------------------------------
class Point3D
{
public:
    Point3D();
    Point3D(double, double, double);

public:
    double X, Y, Z;
};

class Vector3D {
public:
    Vector3D();
    Vector3D(double, double,double);

    double abs() const;
    Vector3D single() const;

public:
    double X, Y, Z;
};

Point3D operator +(const Point3D &, const Vector3D &);
Point3D operator -(const Point3D &, const Vector3D &);

Vector3D operator -(const Point3D &, const Point3D &);
Vector3D operator *(const Vector3D &, const double);

double scalMul(const Vector3D &, const Vector3D &);
double destructBy(const Vector3D &, const Vector3D &);

QString toString(const Point3D &);
QString toString(const Vector3D &);
//-------------------------------------------------------------------------------------------------
class Plane3D {
public:
    Plane3D();
    Plane3D(double, double, double, double);
    Plane3D(const Point3D &, const Vector3D &);

    Point3D project(const Point3D &) const;

public:
    double A, B, C, D;
};
//-------------------------------------------------------------------------------------------------
Point3D rotate_XZ(const Point3D & point, const Point3D & center, float angle);
Point3D rotate_YZ(const Point3D & point, const Point3D & center, float angle);

#endif // POINT3D_H
