#pragma once

#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <list>
#include <memory>


namespace GLUL {

    namespace GUI {

        class GLUL_API RadioButton;

        class GLUL_API RadioButtonGroup : public Component {
            public:
                RadioButton& add(bool set = false);
                void remove(RadioButton& radioButton);

                void set(RadioButton& radioButton);

                Event::HandlerAggregator<Event::ValueChange<RadioButton&>> onValueChange;

            protected:
                RadioButtonGroup(const Container& parent);

                bool _isInGroup(RadioButton& radioButton);
                bool _setDifferentThanCurrent();
                void _pushToBatch(G2D::TexturedBatch& texBatch) const;

                RadioButton* _setButton;
                std::list<std::unique_ptr<RadioButton>> _buttons;

                friend class Container;
        };

    }

}
