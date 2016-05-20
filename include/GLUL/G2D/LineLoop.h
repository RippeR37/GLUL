#pragma once

#include <GLUL/G2D/Point.h>

#include <functional>
#include <initializer_list>
#include <vector>


namespace GLUL {

    namespace G2D {

        class GLUL_API LineLoop : public Primitive {
            public:
                LineLoop();
                LineLoop(const std::vector<Point>& points);
                LineLoop(const std::vector<glm::vec2>& points);
                LineLoop(std::initializer_list<std::reference_wrapper<Point>>& points);
                LineLoop(std::initializer_list<std::reference_wrapper<glm::vec2>>& points);

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                std::vector<Point> points;

            protected:
                void _pushToBatch(GeometryBatch& geometryBatch) const;

                using Primitive::setColor;
        };

    }

}
