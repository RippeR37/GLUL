#include <GLUL/G2D/Circle.h>
#include <GLUL/G2D/TriangleFan.h>

#include <cmath>


namespace GLUL {

    namespace G2D {

        Circle::Circle() : radius(0.0f), pointCount(0u) { }

        Circle::Circle(const Point& center, float radius)
            : center(center), radius(radius), pointCount(defaultPointCount(radius)) { }

        Circle::Circle(const glm::vec2& center, float radius) : Circle(Point { center }, radius) { }

        void Circle::setColor(const glm::vec4& color) {
            center.setColor(color);
        }

        const glm::vec4& Circle::getColor() const {
            return center.getColor();
        }

        unsigned int Circle::defaultPointCount(float radius) {
            unsigned int result;

            result = 4u * std::min(static_cast<unsigned int>(std::sqrt(radius)), 2u) * 4u;

            return result;
        }

        void Circle::_pushToBatch(Batch& batch) const {
            TriangleFan triangleFan;
            Point currentPoint = center;

            // Reserve memory
            triangleFan.points.reserve(2u + pointCount);

            // Center point
            triangleFan.points.push_back(center);

            // Circle points
            const float pi = 3.14159265358979323846f;
            const float pi2 = pi * 2.0f;
            const float steps_div = static_cast<float>(pointCount);

            for(unsigned int i = 0; i <= pointCount; ++i) {
                auto offset = glm::vec2 { std::cos(pi2 * (i / steps_div)), std::sin(pi2 * (i / steps_div)) };

                currentPoint.setPosition(center.getPosition() + (radius * offset));
                triangleFan.points.push_back(currentPoint);
            }

            batch.addPrimitive(triangleFan);
        }

    }

}
