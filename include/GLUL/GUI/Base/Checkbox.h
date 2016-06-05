#pragma once

#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        class GLUL_API Checkbox : public Component {
            public:
                operator bool() const;

                bool getState() const;

                void setState(bool state);

                bool switchState();

                Event::HandlerAggregator<Event::ValueChange<bool>> onValueChange;

            protected:
                Checkbox(const Container& parent, bool state = false);
                Checkbox(const Container& parent, const glm::vec2& size, const glm::vec2& position, bool state = false);

                void _initializeHandlers();
                void _pushToBatch(G2D::TexturedBatch& texBatch) const;

                bool _state;

                friend class Container;
        };

    }

}
