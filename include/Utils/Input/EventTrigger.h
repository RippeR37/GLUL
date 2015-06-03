#ifndef UTILS_INPUT_EVENTTRIGGER_H_INCLUDED
#define UTILS_INPUT_EVENTTRIGGER_H_INCLUDED

#include <Utils/Input/Event.h>
#include <Utils/Input/EventAggregator.h>

#include <functional>
#include <vector>

namespace Util {

    namespace Input {

        class EventTrigger {
            public:
                EventTrigger(EventAggregator& eventAggregator);
                ~EventTrigger();
                
                void reset();

                void setFunction(Event::Type type, const std::function<void(Event&)>& trigger);
                void setFunction(std::initializer_list<Event::Type> types, const std::function<void(Event&)>& trigger);

            private:
                bool _registered;
                unsigned int _triggerID;
                EventAggregator& _eventAggregator;
                std::vector<Event::Type> _types;
        };

    }

}

#endif