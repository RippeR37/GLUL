#ifndef UTILS_LINE_H_INCLUDED
#define UTILS_LINE_H_INCLUDED

#include <Utils/Exception.h>
#include <Utils/Point.h>

#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

namespace Util {

    class Line {
        public:
            Line();
            Line(const Point& start, const Point& end) throw(Exception::FatalError);
            Line(const glm::vec2& start, const glm::vec2& end) throw(Exception::FatalError);
            Line(const Line& line) throw(Exception::FatalError);

            Line& operator=(const Line& line) throw(Exception::FatalError);

            void setLine(const Line& line);
            void setLine(const Point& start, const Point& end) throw(Exception::FatalError);
            void setLine(const glm::vec2& start, const glm::vec2& end) throw(Exception::FatalError);

            double distance(const Point& point) const;
            double distance(const glm::vec2& point) const;

            const Point& getPoint1() const;
            const Point& getPoint2() const;

            const glm::vec2& getPosition1() const;
            const glm::vec2& getPosition2() const;

            glm::vec2 getNormal() const;
            glm::vec2 getReflectedVector(const glm::vec2& inputVector) const;

        public:
            static glm::vec2 getNormal(const Line& line);
            static glm::vec2 getNormal(const glm::vec2& point1, const glm::vec2& point2);

            static glm::vec2 getReflectedVector(const glm::vec2& inputVector, const glm::vec2& normal);

        protected:
            Point _point1;
            Point _point2;
    };

}

#endif