#include <Utils/GL+/GUI/Container.h>

namespace GL {

    namespace GUI {

        Container::Container(Container& parent) : Container(&parent) {

        }

        Container::Container(Container* const parent) : Component(parent) {

        }

        Container::~Container() {
            for(auto& component : _components) {
                component->setParent(nullptr);
                delete component;
                component = nullptr;
            }

            _components.clear();
        }

        void Container::render() const {
            if(!isValid())
                validate();

            for(auto component : _components)
                if(component)
                    component->render();
        }

        void Container::update(double deltaTime) {
            if(!isValid())
                validate();

            for(auto component : _components)
                if(component)
                    component->update(deltaTime);
        }

        void Container::validate() const {
            if(isValid())
                return;

            for(auto component : _components)
                if(component)
                    component->validate();

            const_cast<Container*>(this)->setValid();
        }

        void Container::add(Component& component) {
            add(&component);
        }

        void Container::add(Component* const component) {
            if(component) {
                if(component->getParent() != this) {
                    component->notifyParentOfDestruction();

                    component->setParent(this);
                    _components.push_back(component);
                }
            }
        }

        void Container::setInvalid() {
            Component::setInvalid();

            notifyChildsOfInvalidState();
        }

        void Container::handleInputEvent(const Util::Input::Event& inputEvent) {
            Component::handleInputEvent(inputEvent);
            
            glm::vec2 newPosition;

            const Util::Input::Event* componentEvent = nullptr;
            Util::Input::MouseButtonEvent mouseButtonComponentEvent;
            Util::Input::MouseMovementEvent mouseMovementComponentEvent;

            for(auto component : _components)
                if(component) {
                    componentEvent = nullptr;

                    switch(inputEvent.getType()) {
                        case Util::Input::Event::Type::MouseButton:
                            newPosition = inputEvent.asMouseButtonEvent()->getPosition() - component->getPosition().getPosition();
                            if(newPosition.x >= 0 && newPosition.x < component->getSize().x && 
                               newPosition.y >= 0 && newPosition.y < component->getSize().y) {
                                mouseButtonComponentEvent.setAction(inputEvent.asMouseButtonEvent()->getAction());
                                mouseButtonComponentEvent.setMouseButton(inputEvent.asMouseButtonEvent()->getMouseButton());
                                mouseButtonComponentEvent.setPosition(newPosition);
                                componentEvent = &mouseButtonComponentEvent;
                            }
                            break;

                        case Util::Input::Event::Type::MouseMovement:
                            newPosition = inputEvent.asMouseMovementEvent()->getPosition() - component->getPosition().getPosition();
                            if(newPosition.x >= 0 && newPosition.x < component->getSize().x && 
                               newPosition.y >= 0 && newPosition.y < component->getSize().y) {
                                mouseMovementComponentEvent.setPosition(newPosition);
                                componentEvent = &mouseMovementComponentEvent;
                            }
                            break;

                        default:
                            break;
                    }

                    if(componentEvent != nullptr)
                        component->handleInputEvent(*componentEvent);
                }
        }

        void Container::notifyChildsOfInvalidState() {
            for(auto component : _components)
                if(component)
                    component->setInvalid();
        }

        void Container::handleChildDestruction(Component* component) {
            _components.remove(component);
        }

    }

}