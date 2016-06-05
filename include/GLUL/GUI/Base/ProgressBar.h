#pragma once

#include <GLUL/GUI/Base/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API ProgressBar : public Component {
                public:
                    virtual ~ProgressBar() = default;

                    operator float() const;

                    virtual float getProgress() const;

                    virtual void setProgress(float progress);

                    virtual bool increaseProgress(float value);
                    virtual bool decreaseProgress(float value);

                    Event::HandlerAggregator<Event::ValueChange<float>> onValueChange;

                protected:
                    ProgressBar(const Container& parent, float progress);
                    ProgressBar(const Container& parent, const glm::vec2& size, const glm::vec2& position, float progress);

                    float _progress;

                    friend class Container;
            };

        }

    }

}
