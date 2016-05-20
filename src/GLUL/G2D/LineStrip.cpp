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

        void LineStrip::_pushToBatch(GeometryBatch& geometryBatch) const {
            std::vector<glm::vec4> vertexData;
            std::vector<glm::vec4> colorData;

            for(std::size_t i = 0; i < points.size() - 1; ++i) {
                vertexData.push_back(glm::vec4 { points[  i  ].getPosition(), 0.0f, 1.0f });
                vertexData.push_back(glm::vec4 { points[i + 1].getPosition(), 0.0f, 1.0f });

                colorData.push_back(points[  i  ].getColor());
                colorData.push_back(points[i + 1].getColor());
            }

            _pushDrawCall(geometryBatch, GL::VertexArray::DrawTarget::Lines, vertexData, colorData);
        }

    }

}
