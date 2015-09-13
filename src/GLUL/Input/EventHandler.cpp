#include <GLUL/Input/EventAggregator.h>
#include <GLUL/Input/EventHandler.h>


namespace GLUL {

    namespace Input {
        
        std::unordered_map<Event::Type, std::set<EventAggregator*>, GLUL::Helper::HashEnum> _inputEventAggregators;

        EventHandler::~EventHandler() {
            _unregisterNotifications();
        }

        void EventHandler::_unregisterNotifications() {
            for(auto& typeSet : _inputEventAggregators) {
                for(auto& aggregator : typeSet.second) {
                    aggregator->unregisterHandler(typeSet.first, this, false);
                }
            }

            _inputEventAggregators.clear();
        }
        
        void EventHandler::_removeAggregator(Event::Type type, EventAggregator* eventAggregator) {
            _inputEventAggregators[type].erase(eventAggregator);
        }

    }

}
