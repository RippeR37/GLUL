#include <GLUL/G2D/TriangleStrip.h>


namespace GLUL {

    namespace G2D {

        TriangleStrip::TriangleStrip() { }

        TriangleStrip::TriangleStrip(const std::vector<Point>& points) {
            this->points = points;
        }

        TriangleStrip::TriangleStrip(const std::vector<glm::vec2>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(Point { point });
        }

        TriangleStrip::TriangleStrip(std::initializer_list<std::reference_wrapper<Point>>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(point);
        }

        TriangleStrip::TriangleStrip(std::initializer_list<std::reference_wrapper<glm::vec2>>& points) {
            this->points.reserve(points.size());

            for(auto& point : points)
                this->points.push_back(Point { point });
        }

        void TriangleStrip::setColor(const glm::vec4& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        const glm::vec4& TriangleStrip::getColor() const {
            static glm::vec4 emptyColor;

            if(points.empty())
                return emptyColor;
            else
                return points[0].getColor();
        }

        void TriangleStrip::_pushToBatch(GeometryBatch& geometryBatch) const {
            std::vector<glm::vec4> vertexData;
            std::vector<glm::vec4> colorData;

            for(std::size_t i = 0; i < points.size() - 2; ++i) {
                if(i % 2 == 0) {
                    // Normal order
                    vertexData.push_back(glm::vec4 { points[  i  ].getPosition(), 0.0f, 1.0f });
                    vertexData.push_back(glm::vec4 { points[i + 1].getPosition(), 0.0f, 1.0f });
                    vertexData.push_back(glm::vec4 { points[i + 2].getPosition(), 0.0f, 1.0f });

                    colorData.push_back(points[  i  ].getColor());
                    colorData.push_back(points[i + 1].getColor());
                    colorData.push_back(points[i + 2].getColor());
                } else {
                    // Inverted order
                    // This is to ensure each triangle has same orientation (CW/CCW)
                    vertexData.push_back(glm::vec4 { points[  i  ].getPosition(), 0.0f, 1.0f });
                    vertexData.push_back(glm::vec4 { points[i + 2].getPosition(), 0.0f, 1.0f });
                    vertexData.push_back(glm::vec4 { points[i + 1].getPosition(), 0.0f, 1.0f });

                    colorData.push_back(points[  i  ].getColor());
                    colorData.push_back(points[i + 2].getColor());
                    colorData.push_back(points[i + 1].getColor());
                }
            }

            _pushDrawCall(geometryBatch, GL::VertexArray::DrawTarget::Triangles, vertexData, colorData);
        }

    }

}
