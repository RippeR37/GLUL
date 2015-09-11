#include <GLUL/Line.h>
#include <GLUL/Point.h>
#include <GLUL/Logger.h>

#include <glm/geometric.hpp>


namespace GLUL {

    Line::Line() {
        setLine(Point(0.0f, 0.0f), Point(1.0f, 1.0f));
    }

    Line::Line(const Point& start, const Point& end) {
        setLine(start, end);
    }

    Line::Line(const glm::vec2& start, const glm::vec2& end) {
        setLine(start, end);
    }

    Line::Line(const Line& line) {
        setLine(line.getPoint1(), line.getPoint2());
    }

    Line& Line::operator=(const Line& line) {
        setLine(line.getPoint1(), line.getPoint2());
        return *this;
    }
    
    void Line::setLine(const Line& line) {
        setLine(line.getPoint1(), line.getPoint2());
    }

    void Line::setLine(const Point& start, const Point& end) {
        setLine(start.getPosition(), end.getPosition());
    }

    void Line::setLine(const glm::vec2& start, const glm::vec2& end) {
        if(start == end)
            GLUL::Log::LibraryStream().logWarning("Line should not start and end in same point");

        if(start.x < end.x || (start.x == end.x && start.y < end.y)) {
            _point1 = start;
            _point2 = end;
        } else {
            _point1 = end;
            _point2 = start;
        }
    }

    double Line::distance(const Point& point) const {
        return point.distance(*this);
    }

    double Line::distance(const glm::vec2& point) const {
        return distance(Point(point));
    }

    const Point& Line::getPoint1() const {
        return _point1;
    }

    const Point& Line::getPoint2() const {
        return _point2;
    }

    const glm::vec2& Line::getPosition1() const {
        return _point1.getPosition();
    }

    const glm::vec2& Line::getPosition2() const {
        return _point2.getPosition();
    }

    glm::vec2 Line::getNormal() const {
        float dx = getPosition2().x - getPosition1().x;
        float dy = getPosition2().y - getPosition1().y;

        return glm::normalize(glm::vec2(-dy, dx));
    }
    
    glm::vec2 Line::getReflectedVector(const glm::vec2& inputVector) const {
        return Line::getReflectedVector(inputVector, getNormal());
    }

    glm::vec2 Line::getNormal(const Line& line) {
        return line.getNormal();
    }

    glm::vec2 Line::getNormal(const glm::vec2& point1, const glm::vec2& point2) {
        return Line(point1, point2).getNormal();
    }

    glm::vec2 Line::getReflectedVector(const glm::vec2& inputVector, const glm::vec2& normal) {
        glm::vec2 inputNormalized = glm::normalize(inputVector);

        glm::vec2 u  = (glm::dot(inputNormalized, normal) / glm::dot(normal, normal)) * normal;
        glm::vec2 w  = inputNormalized - u;
        glm::vec2 outputVector = w - u;

        return outputVector;
    }

}
