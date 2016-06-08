#pragma once

#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Shape.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace GLUL {

    namespace G2D {

        class GLUL_API RectangularBorder : public Shape {
        public:
            RectangularBorder();
            RectangularBorder(const glm::vec2& position, float rectangleSize, float borderSize);
            RectangularBorder(const glm::vec2& position, float rectangleSize, float borderSize, const glm::vec3& color);
            RectangularBorder(const glm::vec2& position, float rectangleSize, float borderSize, const glm::vec4& color);
            RectangularBorder(const glm::vec2& position, const glm::vec2& rectangleSize, const glm::vec2& borderSize);
            RectangularBorder(const glm::vec2& position, const glm::vec2& rectangleSize, const glm::vec2& borderSize, const glm::vec3& color);
            RectangularBorder(const glm::vec2& position, const glm::vec2& rectangleSize, const glm::vec2& borderSize, const glm::vec4& color);
            explicit RectangularBorder(const Point& point, float rectangleSize, float borderSize);
            explicit RectangularBorder(const Point& point, const glm::vec2& rectangleSize, const glm::vec2& borderSize);

            void setPosition(const glm::vec2& position);
            void setSize(float size);
            void setSize(const glm::vec2& size);
            void setRectangleSize(float rectangleSize);
            void setRectangleSize(const glm::vec2& rectangleSize);
            void setColor(const glm::vec4& color);

            const glm::vec2& getPosition() const;
            const glm::vec4& getColor() const;
            const glm::vec2& getSize() const;
            const glm::vec2& getRectangleSize() const;

        protected:
            void _pushToBatch(Batch& batch) const;

            glm::vec2 _position;
            glm::vec2 _size;
            glm::vec2 _rectangleSize;
            glm::vec4 _color;

            using Primitive::setColor;
        };

    }

}
