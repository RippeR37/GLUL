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
            std::vector<glm::vec4> vertexData;
            std::vector<glm::vec4> colorData;

            // Add normal lines
            for(std::size_t i = 0; i < points.size() - 1; ++i) {
                vertexData.push_back(glm::vec4 { points[  i  ].getPosition(), 0.0f, 1.0f });
                vertexData.push_back(glm::vec4 { points[i + 1].getPosition(), 0.0f, 1.0f });

                colorData.push_back(points[  i  ].getColor());
                colorData.push_back(points[i + 1].getColor());
            }

            // Add loop's line
            vertexData.push_back(glm::vec4 { points.back().getPosition(),  0.0f, 1.0f });
            vertexData.push_back(glm::vec4 { points.front().getPosition(), 0.0f, 1.0f });

            colorData.push_back(points.back().getColor());
            colorData.push_back(points.front().getColor());

            _pushDrawCall(geometryBatch, GL::VertexArray::DrawTarget::Lines, vertexData, colorData);
        }

    }

}
