#include <Utils/Input/EventAggregator.h>
#include <Utils/Input/EventHandler.h>


namespace Util {

    namespace Input {
        
        std::unordered_map<Event::Type, std::set<EventAggregator*>> _inputEventAggregators;

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

    }

}