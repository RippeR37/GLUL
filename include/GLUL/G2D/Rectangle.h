#pragma once

#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Shape.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace GLUL {

    namespace G2D {

        class GLUL_API Rectangle : public Shape {
            public:
                Rectangle();
                Rectangle(const glm::vec2& position, float size);
                Rectangle(const glm::vec2& position, float size, const glm::vec3& color);
                Rectangle(const glm::vec2& position, float size, const glm::vec4& color);
                Rectangle(const glm::vec2& position, const glm::vec2& size);
                Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
                Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
                explicit Rectangle(const Point& point, float size);
                explicit Rectangle(const Point& point, const glm::vec2& size);

                void setPosition(const glm::vec2& position);
                const glm::vec2& getPosition() const;

                void setSize(float size);
                void setSize(const glm::vec2& size);
                const glm::vec2& getSize() const;

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

            protected:
                void _pushToBatch(GeometryBatch& geometryBatch) const;

                glm::vec2 _position;
                glm::vec2 _size;
                glm::vec4 _color;

                using Primitive::setColor;
            };

    }

}
