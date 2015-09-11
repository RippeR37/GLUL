#pragma once

#include <GLUL/Config.h>
#include <GLUL/Clock.h>
#include <GLUL/TimeEvent.h>

#include <list>
#include <functional>


namespace GLUL {

    class GLUL_API Timer {
        public:
            Timer();

            unsigned int insertEvent(double delay, const std::function<void()>& event); 
            unsigned int insertEvent(const TimeEvent& event); 
            void deleteEvent(unsigned int id);

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
