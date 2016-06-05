#pragma once

#include <GLUL/Config.h>

#include <string>
#include <functional>


namespace GLUL {

    namespace GUI {

        namespace Base {
            class Component;
        }

        namespace Event {

            template<class EventType>
            class EventTemplate {
                public:
                    class Handler {
                        public:
                            typedef std::function<void(Base::Component&, const EventType&)> CallbackType;

                        public:
                            Handler(const std::string& name, const CallbackType& callback) :
                                name(name), callback(callback) { }

                            Handler& operator=(const Handler&) = delete;

                            const std::string name;
                            const CallbackType callback;
                    };

                public:
                    EventTemplate() { }
                    virtual ~EventTemplate() { }

                    EventTemplate& operator=(const EventTemplate&) = delete;
            };

        }

    }

}
