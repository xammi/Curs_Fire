#include "Adjustable.h"
#include <QFile>
#include <QTextStream>

int Adjustable::obj_counter = 1;
//-------------------------------------------------------------------------------------------------
Adjustable::Adjustable() :
    visc(1), diff(1), dt(1), dens_src_power(1), v_up(1), v_side(1), v_flucts(1), u_flucts(1)
{
    filename = ":/adjusts/" + QString::number(obj_counter) + ".adj";
    obj_counter++;
    this->restore();
}

//-------------------------------------------------------------------------------------------------
int Adjustable::getParam(QString name) const {
    if (name == "visc")
        return visc;
    if (name == "diff")
        return diff;
    if (name == "dt")
        return dt;
    if (name == "dens_src")
        return dens_src_power;
    if (name == "v_up")
        return v_up;
    if (name == "v_side")
        return v_side;
    if (name == "v_flucts")
        return v_flucts;
    if (name == "u_flucts")
        return u_flucts;
    return -1;
}

void Adjustable::setParam(QString name, int value) {
    if (name == "visc")
        visc = value;
    if (name == "diff")
        diff = value;
    if (name == "dt")
        dt = value;
    if (name == "dens_src")
        dens_src_power = value;
    if (name == "v_up")
        v_up = value;
    if (name == "v_side")
        v_side = value;
    if (name == "v_flucts")
        v_flucts = value;
    if (name == "u_flucts")
        u_flucts = value;

    this->withSet();
}

QVector<int> Adjustable::getParams() const {
    return { visc, diff, dt, dens_src_power, v_up, v_side, v_flucts, u_flucts };
}

void Adjustable::save() const {
    QFile file(filename);

    QVector<int> params = getParams();
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream( &file);

        for (int param : params)
            stream << param << " ";
    }

    file.close();
}

void Adjustable::restore() {
    QFile file(filename);

    char c;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream( &file);

        stream >> visc >> c;
        stream >> diff >> c;
        stream >> dt >> c;
        stream >> dens_src_power >> c;
        stream >> v_up >> c;
        stream >> v_side >> c;
        stream >> v_flucts >> c;
        stream >> u_flucts >> c;
    }

    file.close();
}
