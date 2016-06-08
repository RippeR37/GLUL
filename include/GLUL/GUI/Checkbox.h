#pragma once

#include <GLUL/Config.h>
#include <GLUL/GUI/Base/Checkbox.h>
#include <GLUL/GUI/RectangularBackground.h>


namespace GLUL {

    namespace GUI {

        namespace Base {
            class Container;
        }

        class GLUL_API Checkbox : public Base::Checkbox {
            public:
                virtual ~Checkbox() = default;

            protected:
                Checkbox(const Base::Container& parent, bool isSet = false);
                Checkbox(const Base::Container& parent, float size, const glm::vec2& position, bool isSet = false);
                Checkbox(const Base::Container& parent, const glm::vec2& size, const glm::vec2& position, bool isSet = false);

                virtual void _pushToBatch(G2D::TexturedBatch& texBatch) const;
                virtual void _pushMarkToBatch(G2D::TexturedBatch& texBatch) const;

                friend class Base::Container;
        };

    }

}
