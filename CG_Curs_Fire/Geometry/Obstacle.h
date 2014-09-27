#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Drawable.h"

//-------------------------------------------------------------------------------------------------
enum struct Matter { STONE, WOOD, IRON };

struct Edge {
    Edge() {}
    Edge(int _f, int _t) : from(_f), to(_t) {}
    int from, to;
};

typedef QVector<Edge> Edges;
typedef std::pair<int, double> IntDouble;

class Obstacle : public Drawable
{
    Q_OBJECT

public:
    Obstacle();
    Obstacle(double lX, double rX, double lY, double rY, double lZ, double rZ, Matter matter);
    virtual ~Obstacle() {}

    virtual void draw(QPainter &, const Projector &, const Plane3D &);
    virtual void updateByTimer();
    void setMatter(Matter);

private:
    int findInvisible(const Points3D &, const Plane3D &);

protected:
    Matter matter;
};

//-------------------------------------------------------------------------------------------------

#endif // OBSTACLE_H
