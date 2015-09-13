#include <GLUL/GUI/Container.h>


namespace GLUL {

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
        
        void Container::setFocused(bool flag) {
            Component::setFocused(flag);

            for(auto component : _components)
                if(component)
                    component->setFocused(flag);
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
            // KeyStroke
            onKeyStroke += Event::KeyStroke::Handler(
                "__GLUL::GUI::Event::KeyStroke::Forwarding", 
                [&](Component& container, const Event::KeyStroke& onKeyStrokeEvent) {
                    (void) container; // skip it

                    for(Component* componentPtr : _components) {
                        Component& component = *componentPtr;

                        if(component.isEnabled() && component.isFocused()) {
                            component.onKeyStroke(component, onKeyStrokeEvent);
                        }
                    }
                }
            );

            // MouseClick
            onMouseClick += Event::MouseClick::Handler(
                "__GLUL::GUI::Event::MouseClick::Forwarding", 
                [&](Component& container, const Event::MouseClick& onMouseClickEvent) {
                    (void) container; // skip it

                    for(Component* componentPtr : _components) {
                        Component& component = *componentPtr;
                        glm::vec2 newPosition = onMouseClickEvent.position - component.getPosition().getPosition();

                        if(newPosition.x >= 0 && newPosition.x < component.getSize().x && 
                           newPosition.y >= 0 && newPosition.y < component.getSize().y)
                        {
                            if(component.isEnabled() && component.isVisible()) {
                                component.onMouseClick(component, Event::MouseClick(onMouseClickEvent.button, newPosition));
                            }
                        }
                    }
                }
            );

            // MouseRelease
            onMouseRelease += Event::MouseRelease::Handler(
                "__GLUL::GUI::Event::MouseRelease::Forwarding", 
                [&](Component& container, const Event::MouseRelease& onMouseReleaseEvent) {
                    (void) container; // skip it

                    for(Component* componentPtr : _components) {
                        Component& component = *componentPtr;
                        glm::vec2 newPosition = onMouseReleaseEvent.position - component.getPosition().getPosition();

                        if(newPosition.x >= 0 && newPosition.x < component.getSize().x && 
                           newPosition.y >= 0 && newPosition.y < component.getSize().y)
                        {
                            if(component.isEnabled() && component.isVisible()) {
                                if(component.isFocused() == false) {
                                    component.setFocused(true);
                                }

                                component.onMouseRelease(component, Event::MouseRelease(onMouseReleaseEvent.button, newPosition));
                            }
                        } else {
                            if(component.isFocused() == true) {
                                component.setFocused(false);
                            }
                        }
                    }
                }
            );

            // MouseLeave
            onMouseLeave += Event::MouseLeave::Handler(
                "__GLUL::GUI::Event::MouseLeave::Forwarding", 
                [&](Component& container, const Event::MouseLeave& onMouseLeaveEvent) {
                    (void) container; // skip it
                    (void) onMouseLeaveEvent; // skip it

                    for(Component* componentPtr : _componentsUnderMouse) {
                        Component& component = *componentPtr;

                        if(component.isEnabled() && component.isVisible()) {
                            component.onMouseLeave(component, Event::MouseLeave());
                        }
                    }

                    _componentsUnderMouse.clear();
                }
            );

            // MouseEnter
            onMouseEnter += Event::MouseEnter::Handler(
                "__GLUL::GUI::Event::MouseEnter::Forwarding", 
                [&](Component& container, const Event::MouseEnter& onMouseEnterEvent) {
                    (void) container; // skip it

                    for(Component* componentPtr : _components) {
                        Component& component = *componentPtr;
                        glm::vec2 newPosition = onMouseEnterEvent.position - component.getPosition().getPosition();

                        if(newPosition.x >= 0 && newPosition.x < component.getSize().x && 
                           newPosition.y >= 0 && newPosition.y < component.getSize().y)
                        {
                            _componentsUnderMouse.insert(componentPtr);
                            component.onMouseEnter(component, Event::MouseEnter(newPosition));
                        }
                    }
                }
            );

            // MouseMove
            onMouseMove += Event::MouseMove::Handler(
                "__GLUL::GUI::Event::MouseLeave::Forwarding", 
                [&](Component& container, const Event::MouseMove& onMouseMoveEvent) {
                    (void) container; // skip it

                    for(Component* componentPtr : _components) {
                        Component& component = *componentPtr;
                        glm::vec2 newPosition = onMouseMoveEvent.position - component.getPosition().getPosition();

                        bool isUnderMouseNow = (newPosition.x >= 0 && newPosition.x < component.getSize().x && 
                                                newPosition.y >= 0 && newPosition.y < component.getSize().y);

                        bool wasUnderMouseBefore = isUnderMouse(componentPtr); // returns result from previous frame !

                        if(isUnderMouseNow) {
                            if(wasUnderMouseBefore) {
                                component.onMouseMove(component, Event::MouseMove(newPosition));
                            } else {
                                _componentsUnderMouse.insert(componentPtr);
                                component.onMouseEnter(component, Event::MouseEnter(newPosition));
                            }
                        } else {
                            if(wasUnderMouseBefore) {
                                _componentsUnderMouse.erase(componentPtr);
                                component.onMouseLeave(component, Event::MouseLeave());
                            } 
                        }
                    }
                }
            );

            // TextInput
            onTextInput += Event::TextInput::Handler(
                "__GLUL::GUI::Event::TextInput::Forwarding", 
                [&](Component& container, const Event::TextInput& onTextInputEvent) {
                    (void) container; // skip it

                    for(Component* componentPtr : _components) {
                        Component& component = *componentPtr;

                        if(component.isEnabled() && component.isFocused()) {
                            component.onTextInput(component, onTextInputEvent);
                        }
                    }
                }
            );
        }
        
        bool Container::isUnderMouse(Component* component) const {
            return (_componentsUnderMouse.count(component) > 0);
        }

    }

}
