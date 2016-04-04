#pragma once

#include <GLUL/Config.h>
#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <vector>


namespace GLUL {

    namespace GUI {

        class GLUL_API RadioButton;

        class GLUL_API RadioButtonGroup {
            public:
                RadioButtonGroup(Container& parent);
                RadioButtonGroup(Container* const parent = nullptr);
                ~RadioButtonGroup();

                RadioButton& create();
                void remove(RadioButton& radioButton);

                void set(RadioButton& radioButton);

            public:
                Event::HandlerAggregator<Event::ValueChange<RadioButton&>> onValueChange;

            private:
                Container* _parent;
                RadioButton* _setButton;
                std::vector<RadioButton*> _buttons;
        };

    }

}