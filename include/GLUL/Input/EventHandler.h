#pragma once

#include <GLUL/Config.h>
#include <GLUL/Helpers/HashEnum.h>
#include <GLUL/Input/Event.h>
#include <GLUL/Input/Types.h>

#include <set>
#include <unordered_map>


namespace GLUL {

    namespace Input {

        class EventAggregator;

        class GLUL_API EventHandler {
            friend class EventAggregator;

            public:
                virtual ~EventHandler();

                virtual void handleInputEvent(const Event& inputEvent) = 0;

            private:
                void _unregisterNotifications();
                void _removeAggregator(Event::Type type, EventAggregator* eventAggregator);

                std::unordered_map<Event::Type, std::set<EventAggregator*>, Helper::HashEnum> _inputEventAggregators;
        };

    }

}
