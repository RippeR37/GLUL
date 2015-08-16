#include <Utils/GL+/GUI/Container.h>

namespace GL {

    namespace GUI {

        Container::Container(Container& parent) : Container(&parent) { }

        Container::Container(Container* const parent) : Component(parent) {
            initializeEventForwarding();
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

        void Container::notifyChildsOfInvalidState() {
            for(auto component : _components)
                if(component)
                    component->setInvalid();
        }

        void Container::handleChildDestruction(Component* component) {
            _components.remove(component);
        }
        
        void Container::initializeEventForwarding() {
            // MouseClick
            onMouseClick += Event::MouseClick::Handler(
                "__UtilLib::GUI::Event::MouseClick::Forwarding", 
                [&](Component& container, const Event::MouseClick& onMouseClickEvent) {
                    (void) container; // skip it

                    for(Component* componentPtr : _components) {
                        Component& component = *componentPtr;
                        glm::vec2 newPosition = onMouseClickEvent.position - component.getPosition().getPosition();

                        if(newPosition.x >= 0 && newPosition.x < component.getSize().x && 
                           newPosition.y >= 0 && newPosition.y < component.getSize().y)
                        {
                            component.onMouseClick(component, Event::MouseClick(onMouseClickEvent.button, newPosition));
                        }
                    }
                }
            );

            // MouseRelease
            onMouseRelease += Event::MouseRelease::Handler(
                "__UtilLib::GUI::Event::MouseRelease::Forwarding", 
                [&](Component& container, const Event::MouseRelease& onMouseReleaseEvent) {
                    (void) container; // skip it

                    for(Component* componentPtr : _components) {
                        Component& component = *componentPtr;
                        glm::vec2 newPosition = onMouseReleaseEvent.position - component.getPosition().getPosition();

                        if(newPosition.x >= 0 && newPosition.x < component.getSize().x && 
                           newPosition.y >= 0 && newPosition.y < component.getSize().y)
                        {
                            component.onMouseRelease(component, Event::MouseRelease(onMouseReleaseEvent.button, newPosition));
                        }
                    }
                }
            );
        }

    }

}