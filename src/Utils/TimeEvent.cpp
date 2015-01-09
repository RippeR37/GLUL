#include <Utils/TimeEvent.h>

namespace Util {
    
    TimeEvent::TimeEvent(double time, const std::function<void()>& delayedEvent) :
        _time(time), _delayedEvent(delayedEvent), _id(TimeEvent::getNewID()), 
        _type(Type::DelayedEvent), _isDone(false) { }

    
    TimeEvent::TimeEvent(const std::function<void(TimeEvent& event, double deltaTime)>& updateEvent) :
        _updateEvent(updateEvent), _id(TimeEvent::getNewID()), 
        _type(Type::UpdateEvent), _isDone(false) { }

    bool TimeEvent::operator==(const TimeEvent& e) {
        return getID() == e.getID();
    }

    void TimeEvent::execute() {
        if(_type == Type::DelayedEvent)
            _delayedEvent();
    }

    void TimeEvent::execute(double deltaTime) {
        if(_type == Type::UpdateEvent) 
            _updateEvent(*this, deltaTime);
    }

    void TimeEvent::setTime(double time) {
        _time = time;
    }

    void TimeEvent::setDone() {
        _isDone = true;
    }

    TimeEvent::Type TimeEvent::getType() const {
        return _type;
    }

    bool TimeEvent::isDone() const {
        if(getType() == Type::DelayedEvent)
            return (getTime() <= 0);

        return _isDone;
    }

    double TimeEvent::getTime() const {
        return _time;
    }

    unsigned int TimeEvent::getID() const {
        return _id;
    }

    unsigned int TimeEvent::getNewID() {
        static unsigned int nextID = 0;

        return nextID++;
    }

}