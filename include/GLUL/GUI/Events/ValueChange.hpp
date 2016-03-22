#pragma once

#include <GLUL/GUI/Events/EventTemplate.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Event {

            template<typename ValueType>
            class ValueChange : public EventTemplate<ValueChange<ValueType>> {
                public:
                    ValueChange(const ValueType& oldValue, const ValueType& newValue)
                        : oldValue(oldValue), newValue(newValue) { }

                    ValueChange& operator=(const ValueChange&) = delete;

                    ValueType oldValue;
                    ValueType newValue;
            };

        }

    }

}
