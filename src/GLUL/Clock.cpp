#include <GLUL/Clock.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>


namespace GLUL {

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
