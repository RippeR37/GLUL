#pragma once

#include <GLUL/Config.h>

#include <string>
#include <functional>


namespace GLUL {

    namespace GUI {

        class Component;

        namespace Event {

            template<class EventType>
            class GLUL_API EventTemplate {
                public:
                    class GLUL_API Handler {
                        public:
                            typedef std::function<void(Component&, const EventType&)> CallbackType;

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
