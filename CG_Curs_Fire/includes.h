#ifndef INCLUDES_H
#define INCLUDES_H

//-------------------------------------------------------------------------------------------------

#include <QDebug>
#include <QVector>
#include <QList>
#include <QString>

#include <QPainter>
#include <QPoint>
#include <QPointF>

#include <functional>
using std::function;

#include <QMetaType>
//-------------------------------------------------------------------------------------------------
struct Exception {
    virtual QString toString() { return ""; }
};

Q_DECLARE_METATYPE(Exception)
//-------------------------------------------------------------------------------------------------
#endif // INCLUDES_H
