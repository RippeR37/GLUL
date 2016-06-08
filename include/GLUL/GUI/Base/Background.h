#pragma once

#include <GLUL/Config.h>
#include <GLUL/GUI/Base/Border.h>


namespace GLUL {

    namespace G2D {
        class TexturedBatch;
    }

    namespace GUI {

        namespace Base {

            class GLUL_API Component;

            class GLUL_API Background {
                public:
                    Background(const Component& owner);
                    virtual ~Background() = default;

                    Background(const Background&) = delete;
                    Background& operator=(const Background&) = delete;

                    Border border;

                protected:
                    void _invalidate();
                    glm::vec2 _getOwnersRealScreenPosition() const;
                    virtual void _pushToBatch(G2D::TexturedBatch& texBatch) = 0;

                    const Component& _owner;

                    friend class ComponentWithBackground;
            };

        }

    }

}
