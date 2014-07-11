#include "Obstacle.h"

//-------------------------------------------------------------------------------------------------
Obstacle::Obstacle() :
    Drawable(), matter(Matter::STONE)
{}

Obstacle::Obstacle(double _lX, double _rX, double _lY, double _rY, double _lZ, double _rZ, Matter _matter) :
    Drawable(_lX, _rX, _lY, _rY, _lZ, _rZ), matter(_matter)
{}

//-------------------------------------------------------------------------------------------------
void Obstacle::draw(QPainter & painter, const Projector & projector) {
    Point3D left(lX, lY, lZ);
    Point3D right(rX, rY, rZ);

    Vector3D dX(rX - lX, 0, 0);
    Vector3D dY(0, rY - lY, 0);
    Vector3D dZ(0, 0, rZ - lZ);

    auto drawLine = [ & painter, & projector ] (const Point3D & from, const Point3D & to) {
        painter.drawLine(projector(from), projector(to));
    };

    drawLine(left, left + dX);
    drawLine(left, left + dY);
    drawLine(left, left + dZ);

    drawLine(right, right - dX);
    drawLine(right, right - dY);
    drawLine(right, right - dZ);

    drawLine(left + dX, right - dY);
    drawLine(left + dX, right - dZ);

    drawLine(left + dY, right - dX);
    drawLine(left + dY, right - dZ);

    drawLine(left + dZ, right - dY);
    drawLine(left + dZ, right - dX);
}
