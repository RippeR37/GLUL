#pragma once

#include <GLUL/Config.h>
#include <GLUL/GUI/Events/EventTemplate.hpp>

#include <string>
#include <map>


namespace GLUL {

    namespace GUI {

        namespace Event {

            template<class EventType>
            class GLUL_API HandlerAggregator {
                public:
                    HandlerAggregator& operator+=(const typename EventTemplate<EventType>::Handler& handler) {
                        return add(handler);
                    }

                    HandlerAggregator& operator-=(const std::string& handlerName) {
                        return remove(handlerName);
                    }

                    void operator()(Component& component, const EventType& eventArg) {
                        call(component, eventArg);
                    }

                    HandlerAggregator& add(const typename EventTemplate<EventType>::Handler& handler) {
                        _handlers[handler.name] = handler.callback;
                        return *this;
                    }

                    HandlerAggregator& remove(const std::string& handlerName) {
                        _handlers.erase(handlerName);
                        return *this;
                    }

                    void call(Component& component, const EventType& eventArg) {
                        for(auto& handlerEntry : _handlers) {
                            handlerEntry.second(component, eventArg); // handlerEntry is std::pair of (handlerName, handler)
                        }
                    }

                private:
                    std::map<std::string, typename EventTemplate<EventType>::Handler::CallbackType> _handlers;
            };

        }

    }

}
