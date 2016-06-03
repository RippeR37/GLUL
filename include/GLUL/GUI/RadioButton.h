#pragma once

#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>


namespace GLUL {

    namespace GUI  {

        class GLUL_API RadioButtonGroup;

        class GLUL_API RadioButton : public Component {
            public:
                operator bool() const;

                bool getState() const;

                void set();

                Event::HandlerAggregator<Event::ValueChange<bool>> onValueChange;

            protected:
                RadioButton(const Container& parent, RadioButtonGroup& group, bool state = false);
                RadioButton(const Container& parent, RadioButtonGroup& group,
                    const glm::vec2& size, const glm::vec2& position, bool state = false);

                void _initializeHandlers();
                void _setState(bool state);
                void _pushToBatch(G2D::TexturedBatch& texBatch) const;

                bool _state;
                RadioButtonGroup& _group;

                friend class RadioButtonGroup;
        };

    }

}
