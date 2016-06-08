#pragma once

#include <GLUL/Config.h>
#include <GLUL/GUI/Base/Background.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace GLUL {

    namespace GUI {

        class GLUL_API RectangularBackground : public Base::Background {
            public:
                RectangularBackground(const Base::Component& owner);
                RectangularBackground(const Base::Component& owner, const glm::vec3& color);
                RectangularBackground(const Base::Component& owner, const glm::vec4& color);
                virtual ~RectangularBackground() = default;

                const glm::vec4& getColor() const;

                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);

            protected:
                virtual void _pushToBatch(G2D::TexturedBatch& texBatch);
                virtual void _pushBorderToBatch(G2D::TexturedBatch& texBatch);
                virtual void _pushBackgroundToBatch(G2D::TexturedBatch& texBatch);

                glm::vec4 _color;
        };

    }

}
