#include <GLUL/TimeLoop.h>

#include <algorithm>

namespace GLUL {

    TimeLoop::TimeLoop() {
        _accumulator = 0.0;
    }

    void TimeLoop::fixed(double time, double timeStep, const std::function<void(double deltaTime)>& function) {
        _accumulator += time;

        while(_accumulator > timeStep) {
            function(timeStep);
            _accumulator -= timeStep;
        }
    }

    void TimeLoop::variable(double time, const std::function<void(double deltaTime)>& function) {
        function(time);
    }

    void TimeLoop::semiFixed(double time, double timeStep, const std::function<void(double deltaTime)>& function) {
        double currentTimeStep;

        while(time > 0) {
            currentTimeStep = std::min(time, timeStep);
            function(currentTimeStep);
            time -= timeStep;
        }
    }

}