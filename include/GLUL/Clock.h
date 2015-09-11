#pragma once

#include <GLUL/Config.h>


namespace GLUL {

    class GLUL_API Clock {
        public:
            Clock();

            double reset();
            double getElapsedTime();

            static double now();

        private:
            void setStartTime(double time);

            double _startTime;
    };

}
