#pragma once

#include <GLUL/GUI/Events/EventTemplate.hpp>

#include <string>


namespace GLUL {

    namespace GUI {

        namespace Event {

            class GLUL_API TextInput : public EventTemplate<TextInput> {
                public:
                    TextInput(const std::string& text);
                    TextInput& operator=(const TextInput&) = delete;

                    const std::string text;
            };

        }

    }

}
