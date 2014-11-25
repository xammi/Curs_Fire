#include "Obstacle.h"


bool Obstacle::Edge::isInvisible(int inv) const {
    return from == inv || to == inv;
}

bool Obstacle::Facet::isInvisible(int inv) const {
    for (int I = 0; I < tops.size(); I++) {
        if (tops[I] == inv)
            return true;
    }
    return false;
}
//-------------------------------------------------------------------------------------------------

Obstacle::Obstacle() :
    Drawable(), matter(STONE)
{}

Obstacle::Obstacle(double _lX, double _rX, double _lY, double _rY, double _lZ, double _rZ, Matter _matter) :
    Drawable(_lX, _rX, _lY, _rY, _lZ, _rZ)
{
    this->setMatter(_matter);
    this->buildDefault();
}

void Obstacle::setMatter(Matter matter) {
    this->matter = matter;

    if (matter == OAK)
        texture = new QPixmap(":/textures/oak");
    else if (matter == BIRCH)
        texture = new QPixmap(":/textures/birch");
    else if (matter == STONE)
        texture = new QPixmap(":/textures/stone");
    else
        texture = NULL;
}

Obstacle::~Obstacle() {
    if (texture) delete texture;
}

void Obstacle::buildDefault() {
    Point3D left(lX, lY, lZ),
            right(rX, rY, rZ);

    Vector3D dX(rX - lX, 0, 0),
             dY(0, rY - lY, 0),
             dZ(0, 0, rZ - lZ);

    tops = {left, left + dX, left + dY, left + dZ,
            right - dZ, right - dX, right - dY, right};

    edges = { Edge(0,1), Edge(0,2), Edge(0,3), Edge(1,4),
              Edge(1,6), Edge(2,4), Edge(2,5), Edge(3,5),
              Edge(3,6), Edge(4,7), Edge(5,7), Edge(6,7) };

    facets = { Facet({ 0, 1, 2, 4 }), Facet({ 0, 1, 6, 3 }), Facet({ 0, 2, 5, 3 }),
               Facet({ 1, 4, 7, 6 }), Facet({ 2, 4, 7, 5 }), Facet({ 3, 6, 7, 5 }) };
}
//-------------------------------------------------------------------------------------------------
void Obstacle::draw(QPainter & painter, const Projector & projector, const Plane3D & plane) {    

    QPoints Ps(8, QPoint(0, 0));
    for (int I = 0; I < tops.size(); ++I)
        Ps[I] = projector(tops[I]);

    int invisible = findInvisible(plane);
    for (Edge & edge : edges)
        if (! edge.isInvisible(invisible))
            painter.drawLine(Ps[edge.from], Ps[edge.to]);

    for (Facet & facet : facets)
        if (! facet.isInvisible(invisible)) {
            QPolygon polygon;

            for (int index : facet.tops)
                polygon.append(Ps[index]);

            painter.setBrush(QBrush(* texture));
            painter.drawPolygon(polygon);
        }
}

int Obstacle::findInvisible(const Plane3D & plane) {
    double maxDist = 0;
    int invisible = -1;
    for (int I = 0; I < tops.size(); ++I) {
        double dist = plane.dist(tops[I]);
        if (invisible == -1 || maxDist < dist) {
            maxDist = dist;
            invisible = I;
        }
    }

    return invisible;
}
