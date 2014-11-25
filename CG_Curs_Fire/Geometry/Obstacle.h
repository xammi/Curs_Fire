#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Drawable.h"

//-------------------------------------------------------------------------------------------------
class Obstacle : public Drawable
{
    Q_OBJECT

private:
    struct Edge {
        Edge() {}
        Edge(int _f, int _t) : from(_f), to(_t) {}

        bool isInvisible(int inv) const;

        int from, to;
    };

    struct Facet {
        Facet() {}
        Facet(const Ints & ints) : tops(ints) {}

        bool isInvisible(int inv) const;

        Ints tops;
    };

    typedef QVector<Edge> Edges;
    typedef QVector<Facet> Facets;
    typedef std::pair<int, double> IntDouble;

public:
    enum Matter { STONE, OAK, BIRCH, IRON };

public:
    Obstacle();
    Obstacle(double lX, double rX, double lY, double rY, double lZ, double rZ, Matter matter);
    virtual ~Obstacle();

    virtual void draw(QPainter &, const Projector &, const Plane3D &);
    void setMatter(Matter);

protected:
    void buildDefault();
    int findInvisible(const Plane3D &);

protected:
    Points3D tops;
    Edges edges;
    Facets facets;

    Matter matter;
    QPixmap * texture;
};

//-------------------------------------------------------------------------------------------------

#endif // OBSTACLE_H
