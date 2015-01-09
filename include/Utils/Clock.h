#ifndef UTILS_FILE_H_INCLUDED
#define UTILS_FILE_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>

namespace Util {

    class Clock {
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

#endif