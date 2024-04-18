#include "Timer.h"

namespace tools
{
    Timer::Timer (std::function<void()> fn) : callbackFn (std::move (fn)) {}
    Timer::~Timer() { stopTimer(); }

    Timer& Timer::setCallback (std::function<void()> fn)
    {
        callbackFn = std::move (fn);
        return *this;
    }

    void Timer::timerCallback() { if (callbackFn) callbackFn(); }
}