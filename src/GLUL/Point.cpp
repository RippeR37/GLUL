#include <GLUL/Point.h>
#include <GLUL/Line.h>

#include <glm/geometric.hpp>


namespace GLUL {

    Point::Point() {
        setPoint(glm::vec2(0.0f));
    }

    Point::Point(const Point& point) {
        setPoint(point);
    }

    Point::Point(const glm::vec2& point) {
        setPoint(point);
    }

    Point::Point(const float x, const float y) {
        setPoint(x, y);
    }

    Point& Point::operator=(const Point& point) {
        setPoint(point);

        return *this;
    }

    Point& Point::operator=(const glm::vec2& point) {
        setPoint(point);

        return *this;
    }

    void Point::setPoint(const Point& point) {
        setPoint(point.getPosition());
    }

    void Point::setPoint(const glm::vec2& point) {
        _position = point;
    }

    void Point::setPoint(const float x, const float y) {
        setPoint(glm::vec2(x, y));
    }

    double Point::distance(const Point& point) const {
        return glm::distance(getPosition(), point.getPosition());
    }

    double Point::distance(const glm::vec2& point) const {
        return glm::distance(getPosition(), point);
    }

    double Point::distance(const Line& line) const {
        glm::vec2 vec = line.getPosition2() - line.getPosition1();

        float dotProduct = glm::dot(vec, vec);
        float factor = ((getX() - line.getPosition1().x) * vec.x + (getY() - line.getPosition1().y) * vec.y) / dotProduct;

        if(factor > 1)       factor = 1;
        else if(factor < 0)  factor = 0;

        glm::vec2 scaled = line.getPosition1() + factor * vec;
        glm::vec2 dist   = scaled - getPosition();

        return glm::length(dist);
    }

    float Point::getX() const {
        return getPosition().x;
    }

    float Point::getY() const {
        return getPosition().y;
    }

    const glm::vec2& Point::getPosition() const {
        return _position;
    }

}
