#include <Utils/Input/EventAggregator.h>
#include <Utils/Input/EventHandler.h>


namespace Util {

    namespace Input {
        
        std::unordered_map<Event::Type, std::set<EventAggregator*>> _aggregators;


        void EventHandler::_unregisterNotifications() {
            for(auto& typeSet : _aggregators) {
                for(auto& aggregator : typeSet.second) {
                    aggregator->unregisterSubscriber(typeSet.first, this);
                }
            }

            _aggregators.clear();
        }

    }

}