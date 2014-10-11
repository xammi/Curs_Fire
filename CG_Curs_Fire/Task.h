#ifndef TASK_H
#define TASK_H

#include "includes.h"
#include "Geometry/Drawable.h"

typedef std::function<void (Drawable *)> TaskCall;

//-------------------------------------------------------------------------------------------------
class Task : public QRunnable
{
public:
    Task(Drawable * _drawable, TaskCall _call) : drawable(_drawable), call(_call) {}

    void run() {
        this->call(drawable);
    }

private:
    Drawable * drawable;
    TaskCall call;
};

//-------------------------------------------------------------------------------------------------
#endif // TASK_H
