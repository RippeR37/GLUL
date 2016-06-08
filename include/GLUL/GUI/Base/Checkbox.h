#pragma once

#include <GLUL/GUI/Base/ComponentWithBackground.h>
#include <GLUL/GUI/Base/Mark.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API Checkbox : public ComponentWithBackground {
                public:
                    virtual ~Checkbox() = default;

                    operator bool() const;

                    virtual bool isSet() const;

                    virtual void set(bool state = true);

                    virtual bool switchState();

                    Mark mark;
                    Event::HandlerAggregator<Event::ValueChange<bool>> onValueChange;

                protected:
                    Checkbox(const Container& parent, bool state, Background* background);
                    Checkbox(const Container& parent, const glm::vec2& size, const glm::vec2& position, bool state, Background* background);

                    void _initializeHandlers();

                    bool _state;

                    friend class Container;
            };

        }

    }

}
