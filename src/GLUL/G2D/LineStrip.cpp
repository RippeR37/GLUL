#include <GLUL/G2D/Line.h>
#include <GLUL/G2D/LineStrip.h>


namespace GLUL {

    namespace G2D {

        LineStrip::LineStrip() { }

        LineStrip::LineStrip(const std::vector<Point>& points) {
            this->points = points;
        }

        LineStrip::LineStrip(const std::vector<glm::vec2>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(Point { point });
        }

        LineStrip::LineStrip(std::initializer_list<std::reference_wrapper<Point>>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(point);
        }

        LineStrip::LineStrip(std::initializer_list<std::reference_wrapper<glm::vec2>>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(Point { point });
        }

        void LineStrip::setColor(const glm::vec4& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        const glm::vec4& LineStrip::getColor() const {
            static glm::vec4 emptyColor;

            if(points.empty())
                return emptyColor;
            else
                return points[0].getColor();
        }

        void LineStrip::_pushToBatch(Batch& batch) const {
            for(std::size_t i = 0; i < points.size() - 1; ++i)
                batch.addPrimitive(Line { points[i], points[i + 1] });
        }

    }

}
