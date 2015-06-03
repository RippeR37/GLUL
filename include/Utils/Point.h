#ifndef UTILS_POINT_H_INCLUDED
#define UTILS_POINT_H_INCLUDED

#include <glm/vec2.hpp>

namespace Util {
    
    class Line;

    class Point {
        public:
            Point();
            Point(const Point& point);
            Point(const glm::vec2& point);
            Point(const float x, const float y);

            Point& operator=(const Point& point);
            Point& operator=(const glm::vec2& point);

            void setPoint(const Point& point);
            void setPoint(const glm::vec2& point);
            void setPoint(const float x, const float y);

            double distance(const Point& point) const;
            double distance(const glm::vec2& point) const;
            double distance(const Line& line) const;

            float getX() const;
            float getY() const;
            const glm::vec2& getPosition() const;

        protected:
            glm::vec2 _position;
    };

}

#endif