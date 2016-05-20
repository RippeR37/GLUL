#pragma once

#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Shape.h>


namespace GLUL {

    namespace G2D {

        class GLUL_API TriangleFan : public Shape {
            public:
                TriangleFan();
                TriangleFan(const std::vector<Point>& points);
                TriangleFan(const std::vector<glm::vec2>& points);
                TriangleFan(std::initializer_list<std::reference_wrapper<Point>>& points);
                TriangleFan(std::initializer_list<std::reference_wrapper<glm::vec2>>& points);

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                std::vector<Point> points;

            protected:
                void _pushToBatch(GeometryBatch& geometryBatch) const;
        };

    }

}
