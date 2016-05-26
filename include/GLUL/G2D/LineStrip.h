#pragma once

#include <GLUL/G2D/Point.h>


namespace GLUL {

    namespace G2D {

        class GLUL_API LineStrip : public Primitive {
            public:
                LineStrip();
                LineStrip(const std::vector<Point>& points);
                LineStrip(const std::vector<glm::vec2>& points);
                LineStrip(std::initializer_list<std::reference_wrapper<Point>>& points);
                LineStrip(std::initializer_list<std::reference_wrapper<glm::vec2>>& points);

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                std::vector<Point> points;

            protected:
                void _pushToBatch(Batch& batch) const;

                using Primitive::setColor;
        };

    }

}
