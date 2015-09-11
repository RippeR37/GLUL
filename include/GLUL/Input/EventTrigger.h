#pragma once

#include <GLUL/Config.h>
#include <GLUL/Input/Event.h>
#include <GLUL/Input/EventAggregator.h>

#include <functional>
#include <vector>


namespace GLUL {

    namespace Input {

        class GLUL_API EventTrigger {
            public:
                EventTrigger(EventAggregator& eventAggregator);
                ~EventTrigger();

                EventTrigger& operator=(const EventTrigger&) = delete;
                
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
