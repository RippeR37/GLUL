#pragma once

#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        class GLUL_API ProgressBar : public Component {
            public:
                operator float() const;

                float getProgress() const;

                void setProgress(float progress);

                bool increaseProgress(float value);
                bool decreaseProgress(float value);

                Event::HandlerAggregator<Event::ValueChange<float>> onValueChange;

            protected:
                ProgressBar(const Container& parent, float progress = 0.0f);
                ProgressBar(const Container& parent, const glm::vec2& size, const glm::vec2& position, float progress = 0.0f);

                void _pushToBatch(G2D::TexturedBatch& texBatch) const;

                float _progress;

                friend class Container;
        };

    }

}
