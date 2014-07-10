#ifndef NS_GRID_H
#define NS_GRID_H

#include "exception.h"
#include "tuple"

namespace Core {

#define IX(i, j) ((i) + (N+2) * (j))

class NS_Solver;
//-------------------------------------------------------------------------------------------------
class NS_Grid
{
    friend class NS_Solver;

public:
    NS_Grid(const int);
    ~NS_Grid();

    void set_src();

    bool correct_N(int _N) const { return N == _N; }

    float density(int i, int j) const;
    float min_dens() const;
    float max_dens() const;

private:
    void set_conf();
    void dispose_conf();

    void set_density_src();
    void set_velocity_src();

private:
    int N;
    int size;

    float * u, * u_src;
    float * v, * v_src;
    float * dens, * dens_src;
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

#endif // NS_GRID_H
