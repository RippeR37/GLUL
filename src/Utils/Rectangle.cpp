#include <Utils/Exception.h>
#include <Utils/Rectangle.h>

namespace Util {

    Rectangle::Rectangle() {
        setPoint(Point());
    }

    Rectangle::Rectangle(const Point& point, float width, float height) {
        setPoint(point);
        setSize(width, height);
    }

    Rectangle::Rectangle(float originX, float originY, float width, float height) {
        setPoint(Point(originX, originY));
        setSize(width, height);
    }
    
    bool Rectangle::intersect(const Line& line) const {
        throw Exception::FatalError("Attempt to use not implemented functionality: Rectangle::intersect(line)");
    }

    bool Rectangle::intersect(const Point& point) const {
        throw Exception::FatalError("Attempt to use not implemented functionality: Rectangle::intersect(point)");
    }

    bool Rectangle::intersect(const Rectangle& rectangle) const {
        throw Exception::FatalError("Attempt to use not implemented functionality: Rectangle::intersect(rectangle)");
    }

    const Point& Rectangle::getPoint() const {
        return _point;
    }

    const glm::vec2& Rectangle::getSize() const {
        return _size;
    }

    const glm::vec2& Rectangle::getPosition() const {
        return getPoint().getPosition();
    }

    float Rectangle::getWidth() const {
        return getSize().x;
    }

    float Rectangle::getHeight() const {
        return getSize().y;
    }
            
    void Rectangle::setPoint(const Point& point) {
        _point = point;
    }

    void Rectangle::setSize(const glm::vec2& size) {
        _size = size;
    }

    void Rectangle::setSize(float width, float height) {
        setSize(glm::vec2(width, height));
    }

    void Rectangle::setWidth(float width) {
        _size.x = width;
    }

    void Rectangle::setHeight(float height) {
        _size.y = height;
    }

}