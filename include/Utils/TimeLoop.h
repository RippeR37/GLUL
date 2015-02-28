#ifndef UTILS_TIMELOOP_H_INCLUDED
#define UTILS_TIMELOOP_H_INCLUDED

#include <functional>

namespace Util {

    class TimeLoop {
        public:
            TimeLoop();

            void fixed(double time, double timeStep, const std::function<void(double deltaTime)>& function);
            static void variable(double time, const std::function<void(double deltaTime)>& function);
            static void semiFixed(double time, double timeStep, const std::function<void(double deltaTime)>& function);

        private:
            double _accumulator;
    };

}

#endif