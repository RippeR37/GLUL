#pragma once

#include <GLUL/Config.h>

#include <functional>


namespace GLUL {

    class GLUL_API TimeLoop {
        public:
            TimeLoop();

            void fixed(double time, double timeStep, const std::function<void(double deltaTime)>& function);
            static void variable(double time, const std::function<void(double deltaTime)>& function);
            static void semiFixed(double time, double timeStep, const std::function<void(double deltaTime)>& function);

        private:
            double _accumulator;
    };

}
