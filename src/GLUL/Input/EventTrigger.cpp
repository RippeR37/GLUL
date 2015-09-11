#include <GLUL/Input/EventAggregator.h>
#include <GLUL/Input/EventTrigger.h>


namespace GLUL {

    namespace Input {

        EventTrigger::EventTrigger(EventAggregator& eventAggregator) : _eventAggregator(eventAggregator) {
            _registered = false;
        }

        EventTrigger::~EventTrigger() {
            reset();
        }

        void EventTrigger::reset() {
            if(_registered) {
                for(Event::Type type : _types) {
                    _eventAggregator.unregisterTrigger(type, _triggerID);
                }
            }

            _types.clear();
            _registered = false;
        }

        void EventTrigger::setFunction(Event::Type type, const std::function<void(Event&)>& trigger) {
            reset();

            _triggerID = _eventAggregator.registerTrigger(type, trigger);
            _types = { type };

            _registered = true;
        }
                
        void EventTrigger::setFunction(std::initializer_list<Event::Type> types, const std::function<void(Event&)>& trigger) {
            reset();
            
            _triggerID = _eventAggregator.registerTrigger(types, trigger);
            _types = types;

            _registered = true;
        }

    }

}
