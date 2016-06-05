#pragma once

#include <GLUL/GUI/Base/Component.h>

#include <glm/vec2.hpp>

#include <string>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API Button : public Component {
                public:
                    virtual ~Button() = default;

                protected:
                    Button(const Container& parent);
                    Button(const Container& parent, const glm::vec2& size, const glm::vec2& position);

                    friend class Container;
            };

        }

    }

}
