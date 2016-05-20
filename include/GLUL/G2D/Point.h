#pragma once

#include <GLUL/G2D/Primitive.h>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace G2D {

        class GLUL_API Point : public Primitive {
            public:
                Point();
                Point(const glm::vec2& position);

                Point& operator=(const glm::vec2& position);

                void setPosition(const glm::vec2& position);
                void setPosition(const Point& point);
                const glm::vec2& getPosition() const;

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

            protected:
                void _pushToBatch(GeometryBatch& geometryBatch) const;

                glm::vec2 _position;
                glm::vec4 _color;
        };

    }

}
