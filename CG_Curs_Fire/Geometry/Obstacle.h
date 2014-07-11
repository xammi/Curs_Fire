#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Drawable.h"

//-------------------------------------------------------------------------------------------------
enum struct Matter { STONE, WOOD, IRON };

class Obstacle : public Drawable
{
public:
    Obstacle();
    Obstacle(double lX, double rX, double lY, double rY, double lZ, double rZ, Matter matter = Matter::STONE);

    virtual void draw(QPainter &, const Projector &);
    void setMatter(Matter);

protected:
    Matter matter;
};

//-------------------------------------------------------------------------------------------------

#endif // OBSTACLE_H
