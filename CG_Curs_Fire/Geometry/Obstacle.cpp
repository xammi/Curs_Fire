#include "Obstacle.h"

//-------------------------------------------------------------------------------------------------
Obstacle::Obstacle() :
    Drawable(), matter(Matter::STONE)
{}

Obstacle::Obstacle(double _lX, double _rX, double _lY, double _rY, double _lZ, double _rZ, Matter _matter) :
    Drawable(_lX, _rX, _lY, _rY, _lZ, _rZ), matter(_matter)
{}

//-------------------------------------------------------------------------------------------------
void Obstacle::draw(QPainter & painter, const Projector & projector, const Plane3D & plane) {
    Point3D left(lX, lY, lZ),
            right(rX, rY, rZ);

    Vector3D dX(rX - lX, 0, 0),
             dY(0, rY - lY, 0),
             dZ(0, 0, rZ - lZ);

    Points3D Ps3 = {left, left + dX, left + dY, left + dZ,
                    right - dZ, right - dX, right - dY, right};

    QPoints Ps;
    Ps.fill(QPoint(0,0), 8);
    for (int I = 0; I < Ps3.size(); ++I)
        Ps[I] = projector(Ps3[I]);

    Edges edges = { Edge(0,1), Edge(0,2), Edge(0,3), Edge(1,4),
                    Edge(1,6), Edge(2,4), Edge(2,5), Edge(3,5),
                    Edge(3,6), Edge(4,7), Edge(5,7), Edge(6,7) };

    int invisible = findInvisible(Ps3, plane);
    for (Edge & edge : edges) {
        if (invisible != edge.from && invisible != edge.to)
            painter.drawLine(Ps[edge.from], Ps[edge.to]);
    }
}

int Obstacle::findInvisible(const Points3D & Ps3, const Plane3D & plane) {
    double maxDist = 0;
    int invisible = -1;
    for (int I = 0; I < Ps3.size(); ++I) {
        double dist = plane.dist(Ps3[I]);
        if (invisible == -1 || maxDist < dist) {
            maxDist = dist;
            invisible = I;
        }
    }

    return invisible;
}

void Obstacle::updateByTimer()
{
    // ничего не делать
}
