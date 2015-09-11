#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Container.h>


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

        void Component::validate() const {
            const_cast<Component*>(this)->setValid();
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

        void Component::setEnabled(bool flag) {
            _isEnabled = flag;

            setInvalid();
            validate();
        }
        
        void Component::setFocused(bool flag) {
            _isFocused = flag;

            setInvalid();
            validate();
        }

        void Component::setVisible(bool flag) {
            _isVisible = flag;

            setInvalid();
            validate();
        }

        void Component::setInvalid() {
            _isValid = false;
        }

        void Component::setSize(const glm::vec2& size) {
            _size = size;

            setInvalid();
            validate();
        }
        
        void Component::setPosition(const glm::vec2& position) {
            _position.setPoint(position);

            setInvalid();
            validate();
        }

        void Component::setPosition(const GLUL::Point& position) {
            setPosition(position.getPosition());
        }

        void Component::setValid() {
            _isValid = true;
        }
        
        void Component::setParent(Container* const parent) {
            _parent = parent;
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

    }

}
