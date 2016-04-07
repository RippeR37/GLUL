#pragma once

#include <GLUL/Config.h>
#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <memory>
#include <vector>


namespace GLUL {

    namespace GUI {

        class GLUL_API RadioButton;

        class GLUL_API RadioButtonGroup {
            public:
                RadioButtonGroup(Container& parent);
                RadioButtonGroup(Container* const parent = nullptr);

                RadioButtonGroup(const RadioButtonGroup&) = delete;
                RadioButtonGroup& operator=(const RadioButtonGroup&) = delete;

                RadioButton& create();
                void remove(RadioButton& radioButton);

                void set(RadioButton& radioButton);

            public:
                Event::HandlerAggregator<Event::ValueChange<RadioButton&>> onValueChange;

            private:
                bool _isInGroup(RadioButton& radioButton);
                bool _setDifferentThanCurrent();

                Container* _parent;
                RadioButton* _setButton;
                std::vector<std::unique_ptr<RadioButton>> _buttons;
        };

    }

}
