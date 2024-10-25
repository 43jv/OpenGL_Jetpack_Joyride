#include "timer.h"
#include <GLFW/glfw3.h>

Timer::Timer(double interval)
{
    prev = 0;
    this->interval = interval;
}

bool Timer::processTick()
{
    double cur = glfwGetTime();
    double r = cur - prev;
    if (r < interval)
        return false;
    else
    {
        prev = cur;
        return true;
    }
}
