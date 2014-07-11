#ifndef POINT3D_H
#define POINT3D_H

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

    double abs(const Vector3D &);

public:
    double X, Y, Z;
};

Point3D operator +(const Point3D &, const Vector3D &);
Point3D operator -(const Point3D &, const Vector3D &);

Vector3D operator -(const Point3D &, const Point3D &);
//-------------------------------------------------------------------------------------------------

#endif // POINT3D_H
