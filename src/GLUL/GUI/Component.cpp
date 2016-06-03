#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Container.h>

#include <algorithm>


namespace GLUL {

    namespace GUI {

        Component::Component(const Container& parent) : Component(parent, {}, {}) { }

        Component::Component(const Container& parent, const glm::vec2& size, const glm::vec2& position)
            : _parent(parent), _size(size), _position(position),
              _isEnabled(true), _isFocused(false),
              _isVisible(true), _isValid(false) { }

        void Component::render() const {
            // do nothing
        }

        void Component::update(double deltaTime) {
            if(!isValid())
                validate();

            (void) deltaTime; // unused
        }

        void Component::validate() const {
            _setValid();
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

        bool Component::isUnderMouse() const {
            if(&getParent() == this)
                return false;

            return getParent().isUnderMouse(*this);
        }

        const Container& Component::getParent() const {
            return _parent;
        }

        const glm::vec2& Component::getPosition() const {
            return _position;
        }

        const glm::vec2 Component::getScreenPosition() const {
            if(&getParent() != this)
                return getParent().getScreenPosition() + getPosition();
            else
                return getPosition();
        }

        const glm::vec2& Component::getSize() const {
            return _size;
        }

        const G2D::Rectangle Component::getBounds() const {
            return { Component::getScreenPosition(), getSize() };
        }

        void Component::setInvalid() const {
            _isValid = false;

            getParent().setInvalid();
        }

        void Component::setEnabled(bool flag) {
            _isEnabled = flag;

            setInvalid();
        }

        void Component::setFocused(bool flag) {
            bool wasFocused = isFocused();

            _isFocused = flag;

            setInvalid();

            if(!wasFocused && isFocused())
                onFocus.call(*this, {});
            else if(wasFocused && !isFocused())
                onFocusLoss.call(*this, {});
        }

        void Component::setVisible(bool flag) {
            _isVisible = flag;

            setInvalid();
        }

        void Component::setSize(const glm::vec2& size) {
            _size = size;

            setInvalid();
        }

        void Component::setPosition(const glm::vec2& position) {
            _position = position;

            setInvalid();
        }

        void Component::_setValid() const {
            _isValid = true;
        }

    }

}
