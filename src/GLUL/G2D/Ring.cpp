#include <GLUL/G2D/Circle.h>
#include <GLUL/G2D/Ring.h>
#include <GLUL/G2D/TriangleStrip.h>

#include <cmath>


namespace GLUL {

    namespace G2D {

        Ring::Ring() { }

        Ring::Ring(const Point& center, float innerRadius, float outerRadius)
            : center(center), innerRadius(innerRadius), outerRadius(outerRadius), pointCount(defaultPointCount(outerRadius)) { }

        Ring::Ring(const glm::vec2& center, float innerRadius, float outerRadius)
            : Ring(Point { center }, innerRadius, outerRadius) { }

        void Ring::setColor(const glm::vec4& color) {
            center.setColor(color);
        }

        const glm::vec4& Ring::getColor() const {
            return center.getColor();
        }

        unsigned int Ring::defaultPointCount(float outerRadius) {
            return Circle::defaultPointCount(outerRadius);
        }

        void Ring::_pushToBatch(GeometryBatch& geometryBatch) const {
            TriangleStrip triangleStrip;
            Point currentInnerPoint = center;
            Point currentOuterPoint = center;

            // Reserve memory
            triangleStrip.points.reserve(2 * (pointCount + 1));

            // Ring points
            const float pi = 3.14159265358979323846f;
            const float pi2 = pi * 2.0f;
            const float steps_div = static_cast<float>(pointCount);

            for(unsigned int i = 0; i <= pointCount; ++i) {
                auto offset = glm::vec2 { std::cos(pi2 * (i / steps_div)), std::sin(pi2 * (i / steps_div)) };

                currentInnerPoint.setPosition(center.getPosition() + (innerRadius * offset));
                currentOuterPoint.setPosition(center.getPosition() + (outerRadius * offset));

                triangleStrip.points.push_back(currentInnerPoint);
                triangleStrip.points.push_back(currentOuterPoint);
            }

            geometryBatch.addPrimitive(triangleStrip);
        }

    }

}
