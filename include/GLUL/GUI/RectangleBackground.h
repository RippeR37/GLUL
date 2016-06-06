#pragma once

#include <GLUL/Config.h>
#include <GLUL/GUI/Base/Background.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace GLUL {

    namespace GUI {

        class GLUL_API RectangleBackground : public Base::Background {
            public:
                RectangleBackground(const Base::Component& owner);
                RectangleBackground(const Base::Component& owner, const glm::vec3& color);
                RectangleBackground(const Base::Component& owner, const glm::vec4& color);
                virtual ~RectangleBackground() = default;

                const glm::vec4& getColor() const;

                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);

            protected:
                virtual void _pushToBatch(G2D::TexturedBatch& texBatch);

                glm::vec4 _color;
        };

    }

}
