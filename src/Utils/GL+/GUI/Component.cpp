#include <Utils/GL+/GUI/Component.h>
#include <Utils/GL+/GUI/Container.h>


namespace GL {

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

        const Util::Point& Component::getPosition() const {
            return _position;
        }

        const Util::Point Component::getScreenPosition() const {
            if(getParent())
                return Util::Point(getParent()->getScreenPosition().getPosition() + getPosition().getPosition());
            else
                return getPosition();
        }

        const Util::Rectangle Component::getBounds() const {
            return Util::Rectangle(getPosition(), getSize().x, getSize().y);
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

        void Component::setPosition(const Util::Point& position) {
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
