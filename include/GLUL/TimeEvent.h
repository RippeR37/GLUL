#pragma once

#include <GLUL/Config.h>

#include <functional>


namespace GLUL {

    class GLUL_API TimeEvent {
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
