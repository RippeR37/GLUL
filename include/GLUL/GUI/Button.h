#pragma once

#include <GLUL/Config.h>
#include <GLUL/GUI/Base/Button.h>
#include <GLUL/GUI/RectangularBackground.h>


namespace GLUL {

    namespace GUI {

        namespace Base {
            class Container;
        }

        class GLUL_API Button : public Base::Button {
            public:
                virtual ~Button() = default;

            protected:
                Button(const Base::Container& parent);
                Button(const Base::Container& parent, const glm::vec2& size, const glm::vec2& position);

                virtual void _pushToBatch(G2D::TexturedBatch& texBatch) const;

                friend class Base::Container;
        };

    }

}
