#ifndef ADJUSTABLE_H
#define ADJUSTABLE_H

#include "../includes.h"
//-------------------------------------------------------------------------------------------------
class Adjustable
{
    static int obj_counter;

public:
    Adjustable();
    virtual ~Adjustable() {}

    int getParam(QString name) const;
    void setParam(QString name, int value);
    QVector<int> getParams() const;

    void save() const;
    void restore();

    virtual void withSet() = 0;

protected:
    QString filename;

    int visc, diff, dt;
    int dens_src_power;
    int v_up, v_side;
    int v_flucts, u_flucts;
};
//-------------------------------------------------------------------------------------------------
#endif // ADJUSTABLE_H
