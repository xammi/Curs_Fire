#ifndef ASOLVER_H
#define ASOLVER_H

#include "AbstractGrid.h"

#define F_SWAP(x0, x) {Field tmp = x0; x0 = x; x = tmp;}

typedef FVal Factor;

namespace Core {

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
