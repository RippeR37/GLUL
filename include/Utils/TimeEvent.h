#ifndef UTILS_TIMEEVENT_H_INCLUDED
#define UTILS_TIMEEVENT_H_INCLUDED

#include <functional>

namespace Util {

    class TimeEvent {
        public:
            enum class Type {
                DelayedEvent,
                UpdateEvent
            };

        public:
            TimeEvent(double time, const std::function<void()>& delayedEvent);
            TimeEvent(const std::function<void(TimeEvent&, double)>& updateEvent);

            bool operator==(const TimeEvent& e);

            void execute();
            void execute(double deltaTime);

            void setTime(double time);
            void setDone();
            
            Type getType() const;
            bool isDone() const;
            double getTime() const;
            unsigned int getID() const;

        private:
            static unsigned int getNewID();

            bool _isDone;
            unsigned int _id;
            double _time;
            Type _type;
            std::function<void()> _delayedEvent;
            std::function<void(TimeEvent&, double)> _updateEvent;
    };

}

#endif