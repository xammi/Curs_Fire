#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

struct Exception {
    virtual QString to_string() = 0;
};

#endif // EXCEPTION_H
