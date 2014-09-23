#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Drawable.h"

//-------------------------------------------------------------------------------------------------
enum struct Matter { STONE, WOOD, IRON };

class Obstacle : public Drawable
{
    Q_OBJECT

public:
    Obstacle();
    Obstacle(double lX, double rX, double lY, double rY, double lZ, double rZ, Matter matter = Matter::STONE);
    virtual ~Obstacle() {}

    virtual void draw(QPainter &, const Projector &);
    void setMatter(Matter);

protected:
    Matter matter;
};

//-------------------------------------------------------------------------------------------------

#endif // OBSTACLE_H
