#pragma once

#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Shape.h>


namespace GLUL {

    namespace G2D {

        class GLUL_API TriangleStrip : public Shape {
            public:
                TriangleStrip();
                TriangleStrip(const std::vector<Point>& points);
                TriangleStrip(const std::vector<glm::vec2>& points);
                TriangleStrip(std::initializer_list<std::reference_wrapper<Point>>& points);
                TriangleStrip(std::initializer_list<std::reference_wrapper<glm::vec2>>& points);

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                std::vector<Point> points;

            protected:
                void _pushToBatch(GeometryBatch& geometryBatch) const;

                using Primitive::setColor;
        };

    }

}
