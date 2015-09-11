#include <GLUL/Timer.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace GLUL {

    Timer::Timer() {
        _clock.reset();
    }

    unsigned int Timer::insertEvent(double delay, const std::function<void()>& event) {
        return insertEvent(TimeEvent(delay, event));
    }

    unsigned int Timer::insertEvent(const TimeEvent& event) {
        _events.push_back(event);
        return event.getID();
    }

    void Timer::deleteEvent(unsigned int id) {
        _events.remove_if([id](const TimeEvent& event) -> bool { return event.getID() == id; });
    }

    void Timer::update() {
        double timeElapsed = _clock.getElapsedTime();
        update(timeElapsed);
    }

    void Timer::update(double timeElapsed) {
        _clock.reset();

        for(std::list<TimeEvent>::iterator event = _events.begin(); event != _events.end(); ) {

            switch(event->getType()) {
                case TimeEvent::Type::DelayedEvent:
                    event->setTime(event->getTime() - timeElapsed);
                    if(event->isDone()) 
                        event->execute();
                    break;

                case TimeEvent::Type::UpdateEvent:
                    event->execute(timeElapsed);
                    break;
            }

            if(event->isDone())
                event = _events.erase(event);
            else 
                ++event;
        }
    }
    
    void Timer::resetClock() {
        _clock.reset();
    }

    const std::list<TimeEvent>& Timer::getEvents() const {
        return _events;
    }

}
