#pragma once

#include <GLUL/Config.h>
#include <GLUL/Helpers/HashEnum.h>
#include <GLUL/Input/Event.h>
#include <GLUL/Input/Types.h>

#include <functional>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>


namespace GLUL {

    class Window;

    namespace Input {

        class EventHandler;

        class GLUL_API EventAggregator {
            public:
                EventAggregator();
                EventAggregator(const EventAggregator&) = delete;
                ~EventAggregator();

                EventAggregator& operator=(const EventAggregator&) = delete;
                EventAggregator& operator=(EventAggregator&&) = delete;

                void registerEvent(Event* inputEvent);

                void registerHandler(Event::Type type, EventHandler* inputHandler);
                void registerHandler(std::initializer_list<Event::Type> types, EventHandler* inputHandler);

                unsigned int registerTrigger(Event::Type type, const std::function<void(Event&)>& inputTrigger);
                unsigned int registerTrigger(std::initializer_list<Event::Type> types, const std::function<void(Event&)>& inputTrigger);

                void unregisterHandler(Event::Type type, EventHandler* inputHandler, bool removeFromHandler = true);
                void unregisterHandler(std::initializer_list<Event::Type> types, EventHandler* inputHandler, bool removeFromHandler = true);

                void unregisterTrigger(Event::Type type, unsigned int triggerID);
                void unregisterTrigger(std::initializer_list<Event::Type> types, unsigned int triggerID);

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
                std::unordered_map<Event::Type, std::set<EventHandler*>, Helper::HashEnum> _handlers;
                std::unordered_map<Event::Type, std::unordered_map<unsigned int, std::function<void(Event&)>>, Helper::HashEnum> _triggers;
        };

    }

}
