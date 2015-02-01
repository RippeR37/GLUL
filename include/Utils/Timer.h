#ifndef UTILS_TIMER_H_INCLUDED
#define UTILS_TIMER_H_INCLUDED

#include <Utils/Clock.h>
#include <Utils/TimeEvent.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <list>
#include <functional>

namespace Util {

    class Timer {
        public:
            Timer();

            unsigned int insertEvent(double delay, const std::function<void()>& event); 
            unsigned int insertEvent(const TimeEvent& event); 
            void deleteEvent(int id);

            void update();
            void update(double timeElapsed);
            void resetClock();

            const std::list<TimeEvent>& getEvents() const;

        private:
            Clock _clock;
            std::list<TimeEvent> _events;

        public:
            friend class TimeEvent;
    };

}

#endif