#ifndef UTILS_GL_GUI_EVENTS_EVENTTEMPLATE_HPP_INCLUDED
#define UTILS_GL_GUI_EVENTS_EVENTTEMPLATE_HPP_INCLUDED

#include <Utils/Config.h>

#include <string>
#include <functional>


namespace GL {

    namespace GUI {

        class Component;

        namespace Event {

            template<class EventType>
            class UTILS_API EventTemplate {
                public:
                    class UTILS_API Handler {
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

#endif
