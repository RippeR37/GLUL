#include <Utils/GL+/GUI/Component.h>
#include <Utils/GL+/GUI/Container.h>

namespace GL {

    namespace GUI {

        Component::Component(Container* const parent) {
            clearListeners();
            setParent(parent);
        }

        Component::~Component() {
            notifyDestructionParent();
        }

        void Component::processEvent(const Event& event) {
            for(auto& listener : _listeners[static_cast<int>(event.getType())])
                listener(event);
        }

        void Component::addListener(Event::Type eventType, std::function<void(const Event&)> function) {
            _listeners[static_cast<int>(eventType)].push_back(function);
        }

        void Component::clearListeners() {
            _listeners.clear();
            _listeners.resize(7); // number of possible event types
        }

        void Component::clearListeners(Event::Type eventType) {
            _listeners[static_cast<int>(eventType)].clear();
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
            return Util::Rectangle(_position, _size.x, _size.y);
        }
        
        Container* const Component::getParent() const {
            return _parent;
        }

        void Component::setEnabled(bool flag) {
            _isEnabled = flag;

            notifyInvalidParent();
        }
        
        void Component::setFocused(bool flag) {
            _isFocused = flag;

            notifyInvalidParent();
        }

        void Component::setVisible(bool flag) {
            _isVisible = flag;

            notifyInvalidParent();
        }

        void Component::setSize(const glm::vec2& size) {
            _size = size;

            notifyInvalidParent();
        }

        void Component::setPosition(const Util::Point& position) {
            _position = position;

            notifyInvalidParent();
        }
        
        void Component::setParent(Container* const parent) {
            _parent = parent;
        }

        void Component::notifyDestructionParent() {
            if(getParent())
                getParent()->handleChildDestruction(this);
        }
        
        void Component::notifyInvalidParent() {
            if(getParent())
                getParent()->setInvalid();
        }

    }

}