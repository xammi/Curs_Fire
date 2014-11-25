#include "Prims3d.h"

Point3D::Point3D() :
    X(0), Y(0), Z(0)
{}

Point3D::Point3D(double _X, double _Y, double _Z) :
    X(_X), Y(_Y), Z(_Z)
{}

double dist(const QPoint & P1, const QPoint & P2) {
    int dX = P1.x() - P2.x(),
        dY = P1.y() - P2.y();
    return qSqrt(dX*dX + dY*dY);
}

double dist(const Point3D & P1, const Point3D & P2) {
    double dX = P1.X - P2.X,
           dY = P1.Y - P2.Y,
           dZ = P1.Z - P2.Z;
    return qSqrt(dX*dX + dY*dY + dZ*dZ);
}
//-------------------------------------------------------------------------------------------------
Vector3D::Vector3D() :
    X(0), Y(0), Z(0)
{}

Vector3D::Vector3D(double _X, double _Y, double _Z) :
    X(_X), Y(_Y), Z(_Z)
{}

double Vector3D::abs() const {
    return qSqrt(X * X + Y * Y + Z * Z);
}

Vector3D Vector3D::single() const {
    double len = abs();
    if (len != 0)
        return Vector3D(X / len, Y / len, Z / len);
    return Vector3D(0, 0, 0);
}
//-------------------------------------------------------------------------------------------------
Point3D operator+(const Point3D & point,const Vector3D & direct) {
    return Point3D(point.X + direct.X,
                   point.Y + direct.Y,
                   point.Z + direct.Z);
}

Point3D operator+=(Point3D & point, const Vector3D & direct) {
    point.X += direct.X;
    point.Y += direct.Y;
    point.Z += direct.Z;
    return point;
}

Point3D operator-=(Point3D & point, const Vector3D & direct) {
    point.X -= direct.X;
    point.Y -= direct.Y;
    point.Z -= direct.Z;
    return point;
}

Point3D operator -(const Point3D & point, const Vector3D & direct) {
    return Point3D(point.X - direct.X,
                   point.Y - direct.Y,
                   point.Z - direct.Z);
}

Vector3D operator -(const Point3D & erste, const Point3D & zweite) {
    return Vector3D(erste.X - zweite.X,
                    erste.Y - zweite.Y,
                    erste.Z - zweite.Z);
}

Vector3D operator *(const Vector3D & vector, const double k) {
    return Vector3D(vector.X * k,
                    vector.Y * k,
                    vector.Z * k);
}

QString toString(const Point3D & point) {
    return QString("%1, %2, %3").arg(point.X).arg(point.Y).arg(point.Z);
}

QString toString(const Vector3D & V) {
    return QString("%1, %2, %3").arg(V.X).arg(V.Y).arg(V.Z);
}
//-------------------------------------------------------------------------------------------------
Plane3D::Plane3D() :
    A(0), B(0), C(0), D(0)
{}

Plane3D::Plane3D(double _A, double _B, double _C, double _D) :
    A(_A), B(_B), C(_C), D(_D)
{}

Plane3D::Plane3D(const Point3D & p, const Vector3D & v) :
    A(v.X), B(v.Y), C(v.Z), D(-A*p.X - B*p.Y - C*p.Z)
{}

Point3D Plane3D::project(const Point3D & point) const {
    // решим через параметрическое уравнение прямой, перпендикулярной к данной плоскости
    // и проходящей через точку
    double div = A * point.X + B * point.Y + C * point.Z + D;
    // найдем пересечение прямой с плоскостью
    double t = -div / (A*A + B*B + C*C);
    // координаты точки проекции
    double X = point.X + A*t,
           Y = point.Y + B*t,
           Z = point.Z + C*t;

    return Point3D(X, Y, Z);
}

double Plane3D::dist(const Point3D & point) const {
    // решим через параметрическое уравнение прямой, перпендикулярной к данной плоскости
    // и проходящей через точку
    double div = A * point.X + B * point.Y + C * point.Z + D;
    // найдем пересечение прямой с плоскостью
    double t = -div / (A*A + B*B + C*C);
    // найдем расстояние от точки до плоскости
    return Vector3D(A*t, B*t, C*t).abs();
}
//-------------------------------------------------------------------------------------------------
Point3D rotate_XZ(const Point3D & point, const Point3D & center, float angle) {
    Vector3D vector = point - center;
    double X = vector.X, Z = vector.Z;
    vector.X = X * cos(angle) - Z * sin(angle);
    vector.Z = X * sin(angle) + Z * cos(angle);
    return center + vector;
}

Point3D rotate_YZ(const Point3D & point, const Point3D & center, float angle) {
    Vector3D vector = point - center;
    double Z = vector.Z, Y = vector.Y;
    vector.Z = Z * cos(angle) - Y * sin(angle);
    vector.Y = Z * sin(angle) + Y * cos(angle);
    return center + vector;
}

double scalMul(const Vector3D & V1, const Vector3D & V2) {
    return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}

double destructBy(const Vector3D & V1, const Vector3D & V2) {
    double lenV2 = V2.abs();
    return scalMul(V1, V2) / lenV2 / lenV2;
}
//-------------------------------------------------------------------------------------------------
Polygon3D::Polygon3D(const Point3D & point, const Vector3D & vect1, const Vector3D & vect2) :
    points(QVector<Point3D>(4, point))
{
    points[1] += vect1;
    points[2] = points[1] + vect2;
    points[3] += vect2;
}

void Polygon3D::shift(const Vector3D & direct) {
    for (Point3D & point : points) {
        point += direct;
    }
}

void Polygon3D::shift_X(double dX) {
    for (Point3D & point : points) {
        point.X += dX;
    }
}

void Polygon3D::shift_Y(double dY) {
    for (Point3D & point : points) {
        point.Y += dY;
    }
}

void Polygon3D::shift_Z(double dZ) {
    for (Point3D & point : points) {
        point.Z += dZ;
    }
}
