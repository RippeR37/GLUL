#include <GLUL/G2D/Circle.h>
#include <GLUL/G2D/Disk.h>
#include <GLUL/G2D/TriangleFan.h>
#include <GLUL/G2D/TriangleStrip.h>

#include <cmath>


namespace GLUL {

    namespace G2D {

        Disk::Disk() : innerRadius(0.0f), outerRadius(0.0f), pointCount(0u) { }

        Disk::Disk(const Point& center, float innerRadius, float outerRadius)
            : center(center), innerRadius(innerRadius), outerRadius(outerRadius), pointCount(defaultPointCount(outerRadius)) { }

        Disk::Disk(const glm::vec2& center, float innerRadius, float outerRadius)
            : Disk(Point { center }, innerRadius, outerRadius) { }

        void Disk::setColor(const glm::vec4& color) {
            center.setColor(color);
        }

        const glm::vec4& Disk::getColor() const {
            return getInnerColor();
        }

        void Disk::setInnerColor(const glm::vec3& innerColor) {
            setInnerColor(glm::vec4 { innerColor, getInnerColor().a });
        }

        void Disk::setInnerColor(const glm::vec4& innerColor) {
            center.setColor(innerColor);
        }

        void Disk::setOuterColor(const glm::vec3& outerColor) {
            setOuterColor(glm::vec4 { outerColor, getOuterColor().a });
        }

        void Disk::setOuterColor(const glm::vec4& outerColor) {
            _outerColor = outerColor;
        }

        const glm::vec4& Disk::getInnerColor() const {
            return center.getColor();
        }

        const glm::vec4& Disk::getOuterColor() const {
            return _outerColor;
        }

        unsigned int Disk::defaultPointCount(float outerRadius) {
            return Circle::defaultPointCount(outerRadius);
        }

        void Disk::_pushToBatch(GeometryBatch& geometryBatch) const {
            TriangleFan triangleFan;
            TriangleStrip triangleStrip;
            Point currentInnerPoint = center;
            Point currentOuterPoint1 = center;
            Point currentOuterPoint2 = center;

            currentOuterPoint1.setColor(getOuterColor());
            currentOuterPoint2.setColor(getOuterColor());

            // Reserve memory
            triangleFan.points.reserve(2u + pointCount);
            triangleStrip.points.reserve(2 * (pointCount + 1));

            // Center point
            triangleFan.points.push_back(center);

            // Circle points
            const float pi = 3.14159265358979323846f;
            const float pi2 = pi * 2.0f;
            const float steps_div = static_cast<float>(pointCount);

            for(unsigned int i = 0; i <= pointCount; ++i) {
                auto offset = glm::vec2 { std::cos(pi2 * (i / steps_div)), std::sin(pi2 * (i / steps_div)) };

                currentInnerPoint.setPosition(center.getPosition() + (innerRadius * offset));
                triangleFan.points.push_back(currentInnerPoint);

                currentOuterPoint1.setPosition(center.getPosition() + (innerRadius * offset));
                currentOuterPoint2.setPosition(center.getPosition() + (outerRadius * offset));
                triangleStrip.points.push_back(currentOuterPoint1);
                triangleStrip.points.push_back(currentOuterPoint2);
            }

            geometryBatch.addPrimitive(triangleFan);
            geometryBatch.addPrimitive(triangleStrip);
        }

    }

}
