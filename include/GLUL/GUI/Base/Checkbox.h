#pragma once

#include <GLUL/GUI/Base/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API Checkbox : public Component {
                public:
                    virtual ~Checkbox() = default;

                    operator bool() const;

                    virtual bool getState() const;

                    virtual void setState(bool state);

                    virtual bool switchState();

                    Event::HandlerAggregator<Event::ValueChange<bool>> onValueChange;

                protected:
                    Checkbox(const Container& parent, bool state);
                    Checkbox(const Container& parent, const glm::vec2& size, const glm::vec2& position, bool state);

                    void _initializeHandlers();

                    bool _state;

                    friend class Container;
            };

        }

    }

}
