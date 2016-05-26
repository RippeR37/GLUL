#include <GLUL/G2D/Triangle.h>
#include <GLUL/G2D/TriangleFan.h>


namespace GLUL {

    namespace G2D {

        TriangleFan::TriangleFan() { }

        TriangleFan::TriangleFan(const std::vector<Point>& points) {
            this->points = points;
        }

        TriangleFan::TriangleFan(const std::vector<glm::vec2>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(Point { point });
        }

        TriangleFan::TriangleFan(std::initializer_list<std::reference_wrapper<Point>>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(point);
        }

        TriangleFan::TriangleFan(std::initializer_list<std::reference_wrapper<glm::vec2>>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(Point { point });
        }

        void TriangleFan::setColor(const glm::vec4& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        const glm::vec4& TriangleFan::getColor() const {
            static glm::vec4 emptyColor;

            if(points.empty())
                return emptyColor;
            else
                return points[0].getColor();
        }

        void TriangleFan::_pushToBatch(Batch& batch) const {
            for(std::size_t i = 1; i < points.size() - 1; ++i)
                batch.addPrimitive(Triangle { points[0], points[i], points[i + 1] });
        }

    }

}
