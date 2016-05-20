#pragma once

#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Shape.h>

#include <array>


namespace GLUL {

    namespace G2D {

        class GLUL_API Disk : public Shape {
        public:
            Disk();
            Disk(const Point& center, float innerRadius, float outerRadius);
            Disk(const glm::vec2& center, float innerRadius, float outerRadius);

            void setColor(const glm::vec4& color);
            void setInnerColor(const glm::vec3& innerColor);
            void setInnerColor(const glm::vec4& innerColor);
            void setOuterColor(const glm::vec3& outerColor);
            void setOuterColor(const glm::vec4& outerColor);
            const glm::vec4& getColor() const;
            const glm::vec4& getInnerColor() const;
            const glm::vec4& getOuterColor() const;

            Point center;
            float innerRadius;
            float outerRadius;
            unsigned int pointCount;

            static unsigned int defaultPointCount(float outerRadius);

        protected:
            void _pushToBatch(GeometryBatch& geometryBatch) const;

            glm::vec4 _outerColor;

            using Primitive::setColor;
        };

    }

}
