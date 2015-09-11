#pragma once

#include <GLUL/Config.h>
#include <GLUL/Point.h>


namespace GLUL {

    class GLUL_API Rectangle {
        public:
            Rectangle();
            Rectangle(const Point& point, float width, float height);
            Rectangle(float originX, float originY, float width, float height);
            
            bool intersect(const Line& line) const;
            bool intersect(const Point& point) const;
            bool intersect(const Rectangle& rectangle) const;

            const Point& getPoint() const;
            const glm::vec2& getSize() const;
            const glm::vec2& getPosition() const;
            float getWidth() const;
            float getHeight() const;
            
            void setPoint(const Point& point);
            void setSize(const glm::vec2& size);
            void setSize(float width, float height);
            void setWidth(float width);
            void setHeight(float height);

        private:
            Point _point;
            glm::vec2 _size;
    };

}
