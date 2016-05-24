#pragma once

#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/TexturedPrimitive.h>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace G2D {

        class GLUL_API TexturedPoint {
            public:
                TexturedPoint();
                TexturedPoint(const glm::vec2& position);
                TexturedPoint(const glm::vec2& position, const glm::vec2& texCoords);
                TexturedPoint(const glm::vec2& position, const glm::vec2& texCoords, const glm::vec3& color);
                TexturedPoint(const glm::vec2& position, const glm::vec2& texCoords, const glm::vec4& color);
                explicit TexturedPoint(const Point& point);
                explicit TexturedPoint(const Point& point, const glm::vec2& texCoords);

                void setPosition(const glm::vec2& position);
                void setPosition(const Point& point);
                void setPosition(const TexturedPoint& point);
                void setTexCoords(const glm::vec2& texCoords);
                void setTexCoords(const TexturedPoint& point);
                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);

                const glm::vec2& getPosition() const;
                const glm::vec2& getTexCoords() const;
                const glm::vec4& getColor() const;

            protected:
                glm::vec2 _position;
                glm::vec2 _texCoords;
                glm::vec4 _color;
        };

    }

}
