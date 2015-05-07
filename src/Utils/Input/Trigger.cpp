#include <Utils/Input/EventAggregator.h>
#include <Utils/Input/Trigger.h>

namespace Util {

    namespace Input {

        Trigger::Trigger(EventAggregator& eventAggregator) : _eventAggregator(eventAggregator) {
            _registered = false;
        }

        Trigger::~Trigger() {
            if(_registered)
                unregister();
        }

        void Trigger::setFunction(Event::Type type, const std::function<void(Event&)>& trigger) {
            unregister();

            _triggerID = _eventAggregator.registerTrigger(type, trigger);
            _types = { type };

            _registered = true;
        }
                
        void Trigger::setFunction(std::initializer_list<Event::Type> types, const std::function<void(Event&)>& trigger) {
            unregister();
            
            _triggerID = _eventAggregator.registerTrigger(types, trigger);
            _types = types;

            _registered = true;
        }

        void Trigger::unregister() {
            if(_registered) {
                for(Event::Type type : _types) {
                    _eventAggregator.unregisterTrigger(type, _triggerID);
                }
            }

            _types.clear();
            _registered = false;
        }

    }

}