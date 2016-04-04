#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Container.h>

#include <cmath>


namespace GLUL {

    namespace GUI {

        Component::Component(Container& parent) : Component(&parent) { }

        Component::Component(Container* const parent) {
            setValid();
            setParent(nullptr);
            setVisible(true);
            setEnabled(true);
            setFocused(false);
            setSize(glm::vec2(0.0f));
            setPosition(glm::vec2(0.0f));
            
            setInvalid();

            bindTo(parent);
        }

        Component::~Component() {
            notifyParentOfDestruction();
        }

        void Component::bindTo(Container& container) {
            bindTo(&container);
        }

        void Component::bindTo(Container* container) {
            notifyParentOfDestruction();

            if(container)
                container->add(this);
            else
                setParent(nullptr);
        }

        const Component& Component::validate() const {
            const_cast<Component*>(this)->setValid();

            return *this;
        }
        
        bool Component::isEnabled() const {
            return _isEnabled;
        }

        bool Component::isFocused() const {
            return _isFocused;
        }

        bool Component::isVisible() const {
            return _isVisible;
        }

        bool Component::isValid() const {
            return _isValid;
        }

        const glm::vec2& Component::getSize() const {
            return _size;
        }

        const GLUL::Point& Component::getPosition() const {
            return _position;
        }

        const GLUL::Point Component::getScreenPosition() const {
            if(getParent())
                return GLUL::Point(getParent()->getScreenPosition().getPosition() + getPosition().getPosition());
            else
                return getPosition();
        }

        const GLUL::Rectangle Component::getBounds() const {
            return GLUL::Rectangle(getPosition(), getSize().x, getSize().y);
        }
        
        const Container* Component::getParent() const {
            return _parent;
        }
        
        Container* Component::getParent() {
            return _parent;
        }

        Component& Component::setEnabled(bool flag) {
            _isEnabled = flag;

            setInvalid();
            validate();

            return *this;
        }
        
        Component& Component::setFocused(bool flag) {
            _isFocused = flag;

            setInvalid();
            validate();

            return *this;
        }

        Component& Component::setVisible(bool flag) {
            _isVisible = flag;

            setInvalid();
            validate();

            return *this;
        }

        Component& Component::setInvalid() {
            _isValid = false;

            return *this;
        }

        Component& Component::setSize(const glm::vec2& size) {
            _size = size;

            setInvalid();
            validate();

            return *this;
        }
        
        Component& Component::setPosition(const glm::vec2& position) {
            _position.setPoint(position);

            setInvalid();
            validate();

            return *this;
        }

        Component& Component::setPosition(const GLUL::Point& position) {
            setPosition(position.getPosition());

            return *this;
        }

        Component& Component::setValid() {
            _isValid = true;

            return *this;
        }
        
        Component& Component::setParent(Container* const parent) {
            _parent = parent;

            return *this;
        }

        void Component::notifyParentOfDestruction() {
            if(getParent())
                getParent()->handleChildDestruction(this);
        }
        
        bool Component::isUnderMouse() const {
            if(getParent() == nullptr)
                return false;

            return getParent()->isUnderMouse(const_cast<Component*>(this));
        }

        void Component::pushColoredRectangle(
            std::vector<glm::vec4>& result,
            const glm::vec2& posStart, 
            const glm::vec2& posEnd,
            const glm::vec4& color)
        {
            // Vertices                                                     // Colors
            result.emplace_back(posStart.x, posStart.y, 0.0f, 1.0f);        result.emplace_back(color);
            result.emplace_back(posEnd.x,   posStart.y, 0.0f, 1.0f);        result.emplace_back(color);
            result.emplace_back(posStart.x, posEnd.y,   0.0f, 1.0f);        result.emplace_back(color);

            result.emplace_back(posStart.x, posEnd.y,   0.0f, 1.0f);        result.emplace_back(color);
            result.emplace_back(posEnd.x,   posStart.y, 0.0f, 1.0f);        result.emplace_back(color);
            result.emplace_back(posEnd.x,   posEnd.y,   0.0f, 1.0f);        result.emplace_back(color);
        }

        void Component::pushColoredDisk(
            std::vector<glm::vec4>&result,
            const glm::vec2& posCenter,
            float radius,
            const glm::vec4& color)
        {
            const unsigned int steps = 32;
            const float pi = 3.14159265358979323846f;
            const float pi2 = pi * 2.0f;

            for(unsigned int i = 0, j = i + 1; i < steps; ++i, j = (i+1) % steps) {
                float steps_div = static_cast<float>(steps);

                glm::vec2 offset1 = glm::vec2(std::cos(pi2 * (i / steps_div)), std::sin(pi2 * (i / steps_div)));
                glm::vec2 offset2 = glm::vec2(std::cos(pi2 * (j / steps_div)), std::sin(pi2 * (j / steps_div)));

                glm::vec2 p1 = posCenter;
                glm::vec2 p2 = posCenter + radius * offset1;
                glm::vec2 p3 = posCenter + radius * offset2;

                result.emplace_back(p1.x, p1.y, 0.0f, 1.0f);    result.emplace_back(color);
                result.emplace_back(p2.x, p2.y, 0.0f, 1.0f);    result.emplace_back(color);
                result.emplace_back(p3.x, p3.y, 0.0f, 1.0f);    result.emplace_back(color);
            }
        }

        void Component::pushColoredCircle(
            std::vector<glm::vec4>&result,
            const glm::vec2& posCenter,
            float radius,
            unsigned int width,
            const glm::vec4& color)
        {
            (void) result;
            (void) posCenter;
            (void) radius;
            (void) width;
            (void) color;

            // TODO: implement this with GL_LINES in mind
        }

    }

}
