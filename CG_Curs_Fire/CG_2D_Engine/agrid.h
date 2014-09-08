#ifndef AGRID_H
#define AGRID_H

#include "exception.h"
#include "tuple"

namespace Core {

//-------------------------------------------------------------------------------------------------
class AbstractGrid
{
public:
    AbstractGrid();
};

//-------------------------------------------------------------------------------------------------
// engine utils
void assign(int size, float * src, float * array);
void fill_random(int size, float * src, float from, float to);

float get_max(int size, float * array);
float get_min(int size, float * array);

struct MemNotAlloc : public Exception {
    QString to_string() { return "Memory for grid was not allocated"; }
};

} // namespace Core

#endif // AGRID_H
