#include <GLUL/G2D/Line.h>
#include <GLUL/G2D/LineLoop.h>


namespace GLUL {

    namespace G2D {

        LineLoop::LineLoop() { }

        LineLoop::LineLoop(const std::vector<Point>& points) {
            this->points = points;
        }

        LineLoop::LineLoop(const std::vector<glm::vec2>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(Point { point });
        }

        LineLoop::LineLoop(std::initializer_list<std::reference_wrapper<Point>>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(point);
        }

        LineLoop::LineLoop(std::initializer_list<std::reference_wrapper<glm::vec2>>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(Point { point });
        }

        void LineLoop::setColor(const glm::vec4& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        const glm::vec4& LineLoop::getColor() const {
            static glm::vec4 emptyColor;

            if(points.empty())
                return emptyColor;
            else
                return points[0].getColor();
        }

        void LineLoop::_pushToBatch(GeometryBatch& geometryBatch) const {
            // Normal lines
            for(std::size_t i = 0; i < points.size() - 1; ++i)
                geometryBatch.addPrimitive(Line { points[i], points[i + 1] });

            // Loop's line
            geometryBatch.addPrimitive(Line { points.back(), points.front() });
        }

    }

}
