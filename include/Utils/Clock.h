#ifndef UTILS_FILE_H_INCLUDED
#define UTILS_FILE_H_INCLUDED

#include <Utils/Config.h>


namespace Util {

    class UTILS_API Clock {
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
