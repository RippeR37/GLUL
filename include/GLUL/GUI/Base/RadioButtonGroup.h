#pragma once

#include <GLUL/GUI/Base/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <list>
#include <memory>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API RadioButton;

            class GLUL_API RadioButtonGroup : public Component {
                public:
                    virtual ~RadioButtonGroup() = default;

                    virtual RadioButton& add(bool set) = 0;
                    virtual void remove(RadioButton& radioButton);

                    virtual void set(RadioButton& radioButton);

                    Event::HandlerAggregator<Event::ValueChange<RadioButton&>> onValueChange;

                protected:
                    RadioButtonGroup(const Container& parent);

                    bool _isInGroup(RadioButton& radioButton);
                    bool _setDifferentThanCurrent();
                    RadioButton& _add(bool set, RadioButton* radioButton);

                    RadioButton* _setButton;
                    std::list<std::unique_ptr<RadioButton>> _buttons;

                    friend class Container;
            };

        }

    }

}
