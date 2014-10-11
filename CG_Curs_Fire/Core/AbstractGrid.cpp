#include "AbstractGrid.h"

float transVal(float left, float right, int value) {
    float factor = (right - left) / 100;
    return left + value * factor;
}

namespace Core {
//-------------------------------------------------------------------------------------------------

AbstractGrid::AbstractGrid(const int _N) :
    N(_N), size((_N+2) * (_N+2))
{
}
//-------------------------------------------------------------------------------------------------

} // namespace Core
