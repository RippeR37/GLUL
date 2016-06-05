#pragma once

#include <GLUL/GUI/Base/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>


namespace GLUL {

    namespace GUI  {

        namespace Base {

            class GLUL_API RadioButtonGroup;

            class GLUL_API RadioButton : public Component {
                public:
                    virtual ~RadioButton() = default;

                    operator bool() const;

                    virtual bool isSet() const;

                    virtual void set();

                    Event::HandlerAggregator<Event::ValueChange<bool>> onValueChange;

                protected:
                    RadioButton(const Container& parent, RadioButtonGroup& group, bool state);
                    RadioButton(const Container& parent, RadioButtonGroup& group,
                        const glm::vec2& size, const glm::vec2& position, bool state);

                    void _initializeHandlers();
                    void _setState(bool state);

                    bool _state;
                    RadioButtonGroup& _group;

                    friend class RadioButtonGroup;
            };

        }

    }

}
