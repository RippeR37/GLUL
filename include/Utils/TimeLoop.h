#ifndef UTILS_TIMELOOP_H_INCLUDED
#define UTILS_TIMELOOP_H_INCLUDED

#include <Utils/Config.h>

#include <functional>


namespace Util {

    class UTILS_API TimeLoop {
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
