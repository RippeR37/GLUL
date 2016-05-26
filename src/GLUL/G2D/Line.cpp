#include <GLUL/G2D/Line.h>
#include <GLUL/G2D/Quad.h>

#include <glm/geometric.hpp>


namespace GLUL {

    namespace G2D {

        Line::Line(unsigned int thickness) : points({}) {
            setThickness(thickness);
        }

        Line::Line(const Point& point1, const Point& point2, unsigned int thickness) {
            points[0] = point1;
            points[1] = point2;

            setThickness(thickness);
        }

        Line::Line(const glm::vec2& position1, const glm::vec2& position2, unsigned int thickness)
            : Line(Point { position1 }, Point { position2 }, thickness) { }

        void Line::setColor(const glm::vec4& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        const glm::vec4& Line::getColor() const {
            return points[0].getColor();
        }

        void Line::setThickness(unsigned int thickness) {
            for(auto& point : points)
                point.size = thickness;
        }

        void Line::_pushToBatch(Batch& batch) const {
            Quad quad;
            Point point1 = points[0];
            Point point2 = points[1];

            {
                // Make sure point1 is on left of (or exactly under) point2
                const glm::vec2& pos1 = point1.getPosition();
                const glm::vec2& pos2 = point2.getPosition();

                if(pos1.x > pos2.x || (pos1.x == pos2.x && pos1.y > pos2.y))
                    std::swap(point1, point2);
            }

            std::array<Point, 4> qPoints { { point1, point2, point2, point1 } };
            glm::vec2 lineVector = glm::normalize(point2.getPosition() - point1.getPosition());
            glm::vec2 perpendicularLineVector = { -lineVector.y, lineVector.x };

            qPoints[0].setPosition(point1.getPosition() - (perpendicularLineVector * static_cast<float>(point1.size / 2)));
            qPoints[1].setPosition(point2.getPosition() - (perpendicularLineVector * static_cast<float>(point2.size / 2)));
            qPoints[2].setPosition(point2.getPosition() + (perpendicularLineVector * static_cast<float>(point2.size - (point2.size / 2))));
            qPoints[3].setPosition(point1.getPosition() + (perpendicularLineVector * static_cast<float>(point1.size - (point1.size / 2))));

            quad.points = qPoints;
            batch.addPrimitive(quad);
        }

    }

}
