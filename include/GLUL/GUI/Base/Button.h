#pragma once

#include <GLUL/GUI/Base/ComponentWithBackground.h>

#include <glm/vec2.hpp>

#include <string>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API Button : public ComponentWithBackground {
                public:
                    virtual ~Button() = default;

                protected:
                    Button(const Container& parent, Background* background);
                    Button(const Container& parent, const glm::vec2& size, const glm::vec2& position, Background* background);

                    friend class Container;
            };

        }

    }

}
