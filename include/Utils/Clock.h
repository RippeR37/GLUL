#ifndef UTILS_FILE_H_INCLUDED
#define UTILS_FILE_H_INCLUDED

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