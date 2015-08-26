#include <Utils/Input/EventAggregator.h>
#include <Utils/Input/EventHandler.h>


namespace Util {

    namespace Input {
        
        std::unordered_map<Event::Type, std::set<EventAggregator*>, Util::Helper::HashEnum> _inputEventAggregators;

        EventHandler::~EventHandler() {
            _unregisterNotifications();
        }

        void EventHandler::_unregisterNotifications() {
            for(auto& typeSet : _inputEventAggregators) {
                for(auto& aggregator : typeSet.second) {
                    aggregator->unregisterHandler(typeSet.first, this);
                }
            }

            _inputEventAggregators.clear();
        }
        
        void EventHandler::_removeAggregator(Event::Type type, EventAggregator* eventAggregator) {
            _inputEventAggregators[type].erase(eventAggregator);
        }

    }

}
