#ifndef POINT3D_H
#define POINT3D_H

#include "includes.h"


enum class Axis { OX, OY, OZ };
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

typedef QVector<QPoint> QPoints;
typedef QVector<Point3D> Points3D;

double dist(const QPoint &, const QPoint &);
double dist(const Point3D &, const Point3D &);

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
    double dist(const Point3D &) const;

public:
    double A, B, C, D;
};

class Polygon3D {
public:
    Polygon3D() {}
    Polygon3D(const Point3D & point, const Vector3D &, const Vector3D &);

    void shift_X(double dX);
    void shift_Y(double dY);
    void shift_Z(double dZ);

    void shift(const Vector3D &);

    int size() const { return points.size(); }

    const Point3D & operator[] (int I) const { return points[I];  }
    Point3D & operator[] (int I) { return points[I];  }

private:
    QVector<Point3D> points;
};

//-------------------------------------------------------------------------------------------------
Point3D rotate_XZ(const Point3D & point, const Point3D & center, float angle);
Point3D rotate_YZ(const Point3D & point, const Point3D & center, float angle);

#endif // POINT3D_H
