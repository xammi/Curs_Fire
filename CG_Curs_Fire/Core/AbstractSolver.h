#ifndef ASOLVER_H
#define ASOLVER_H

#include "AbstractGrid.h"

namespace Core {

typedef FVal Factor;

//-------------------------------------------------------------------------------------------------
class AbstractSolver
{
public:
    AbstractSolver(const int _N);

    bool correct_N(int _N) const { return N == _N; }

protected:
    const int N;
    const int size;
};

//-------------------------------------------------------------------------------------------------
struct Wrong_N : public Exception {
    QString to_string() { return "Sent N does not correspond the initial one"; }
};

} // namespace Core

#endif // ASOLVER_H
