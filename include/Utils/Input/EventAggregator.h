#ifndef UTILS_INPUT_EVENTAGGREGATOR_H_INCLUDED
#define UTILS_INPUT_EVENTAGGREGATOR_H_INCLUDED

#include <Utils/Input/Event.h>
#include <Utils/Input/Types.h>

#include <functional>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

namespace Util {

    namespace Input {

        class EventHandler;

        class EventAggregator {
            public:
                EventAggregator();
                ~EventAggregator();

                void registerEvent(Event* inputEvent);
                void registerSubscriber(Event::Type type, EventHandler* inputHandler);
                unsigned int registerTrigger(Event::Type type, const std::function<void(Event&)>& inputTrigger);

                void unregisterSubscriber(Event::Type type, EventHandler* inputHandler);
                void unregisterTrigger(Event::Type type, unsigned int triggerID);

                void notifyAll();

                void clear();
                void clearEvents();
                void clearTriggers();
                void clearSubscribers();

                const std::vector<std::unique_ptr<Event>>& getEvents();


            private:
                unsigned int _getNextTriggerID();

                unsigned int _nextTriggerID;
                std::vector<std::unique_ptr<Event>> _events;
                std::unordered_map<Event::Type, std::set<EventHandler*>> _subscribers;
                std::unordered_map<Event::Type, std::unordered_map<unsigned int, std::function<void(Event&)>>> _triggers;
        };

    }

}

#endif