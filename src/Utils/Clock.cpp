#include <Utils/Clock.h>

namespace Util {

    Clock::Clock() {
        setStartTime(Clock::now());
    }

    double Clock::reset() {
        double now = Clock::now();
        double elapsed = now - _startTime;
        setStartTime(now);
        
        return elapsed;
    }

    double Clock::getElapsedTime() {
        return (Clock::now() - _startTime);
    }

    void Clock::setStartTime(double time) {
        _startTime = time;
    }

    double Clock::now() {
        return glfwGetTime();
    }

}