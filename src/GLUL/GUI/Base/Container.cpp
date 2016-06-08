#include <GLUL/GL++/Context.h>
#include <GLUL/GUI/Base/Container.h>
#include <GLUL/Resources/Fonts.h>

namespace GLUL {

    namespace GUI {

        namespace Base {

            /*
             * GUI::Component (GUI::Window) can't request already created G2D::Font
             * because proper OpenGL context hasn't been created yet!
             * That's why we're creating empty shell of Font object, so it will work as stub.
             * When user will request Container's font, it will be hot-swapped with default font.
             * Container has only const reference of given font, so it can't modify it in any way.
             */
            static G2D::Font _emptyFont;


            Container::Container(const Container& parent) : Container(parent, {}, {}) { }

            Container::Container(const Container& parent, const glm::vec2& size, const glm::vec2& position)
                : Component(parent, size, position), _wasScissorTestActive(false), _font(_emptyFont)
            {
                _initializeEventForwarding();
            }

            void Container::render() const {
                _setupClipping();

                // Render inner containers
                for(const auto& component : _components)
                    component->render();

                // Render components on this level
                _batch.render();

                _revertClipping();
            }

            void Container::update(double deltaTime) {
                if(!isValid())
                    validate();

                for(auto& component : _components)
                    component->update(deltaTime);
            }

            void Container::validate() const {
                if(isValid())
                    return;

                for(const auto& component : _components)
                    component->validate();

                _rebuildBatch();
                _setValid();
            }

            void Container::remove(Component& component) {
                _components.remove_if(
                    [&component](const std::unique_ptr<Component>& iteratedComponent) {
                        return &component == iteratedComponent.get();
                    }
                );

                _componentsUnderMouse.erase(&component);

                setInvalid();
            }

            bool Container::isUnderMouse(const Component& component) const {
                Component* componentPtr = const_cast<Component*>(&component);

                return _componentsUnderMouse.find(componentPtr) != _componentsUnderMouse.end();
            }

            const glm::vec2 Container::getOffset() const {
                return { 0.0f, 0.0f };
            }

            const G2D::Font& Container::getFont() const {
                // If custom font hasn't been asigned, request default one
                if(&_font.get() == &_emptyFont)
                    _font = GLUL::Resources::Fonts::GetDefault();

                return _font;
            }

            void Container::setInvalid() const {
                _isValid = false;
            }

            void Container::setFocused(bool flag) {
                Component::setFocused(flag);

                for(auto& component : _components)
                    component->setFocused(flag);
            }

            void Container::setFont(const G2D::Font& font) {
                _font = font;

                setInvalid();
            }

            void Container::_invalidateComponents() const {
                for(auto& component : _components)
                    component->setInvalid();
            }

            void Container::_initializeEventForwarding() {
                // KeyStroke
                onKeyStroke += Event::KeyStroke::Handler(
                    "__GLUL::GUI::Event::KeyStroke::Forwarding",
                    [&](Component& container, const Event::KeyStroke& onKeyStrokeEvent) {
                        (void) container; // skip it

                        for(auto& component : _components)
                            if(component->isEnabled() && component->isFocused())
                                component->onKeyStroke(*component, onKeyStrokeEvent);
                    }
                );

                // MouseClick
                onMouseClick += Event::MouseClick::Handler(
                    "__GLUL::GUI::Event::MouseClick::Forwarding",
                    [&](Component& container, const Event::MouseClick& onMouseClickEvent) {
                        (void) container; // skip it

                        for(auto& component : _components) {
                            glm::vec2 newPosition = onMouseClickEvent.position - component->getPosition() + getOffset();

                            if(newPosition.x >= 0 && newPosition.x < component->getSize().x &&
                               newPosition.y >= 0 && newPosition.y < component->getSize().y &&
                               component->isEnabled() && component->isVisible())
                            {
                                component->onMouseClick(*component, { onMouseClickEvent.button, newPosition });
                            }
                        }
                    }
                );

                // MouseRelease
                onMouseRelease += Event::MouseRelease::Handler(
                    "__GLUL::GUI::Event::MouseRelease::Forwarding",
                    [&](Component& container, const Event::MouseRelease& onMouseReleaseEvent) {
                        (void) container; // skip it

                        for(auto& component : _components) {
                            glm::vec2 newPosition = onMouseReleaseEvent.position - component->getPosition() + getOffset();

                            if(newPosition.x >= 0 && newPosition.x < component->getSize().x &&
                               newPosition.y >= 0 && newPosition.y < component->getSize().y)
                            {
                                if(component->isEnabled() && component->isVisible()) {
                                    if(component->isFocused() == false)
                                        component->setFocused(true);

                                    component->onMouseRelease(*component, { onMouseReleaseEvent.button, newPosition });
                                }
                            } else {
                                if(component->isFocused() == true)
                                    component->setFocused(false);
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

                        for(auto component : _componentsUnderMouse)
                            if(component->isEnabled() && component->isVisible())
                                component->onMouseLeave(*component, { });

                        _componentsUnderMouse.clear();
                    }
                );

                // MouseEnter
                onMouseEnter += Event::MouseEnter::Handler(
                    "__GLUL::GUI::Event::MouseEnter::Forwarding",
                    [&](Component& container, const Event::MouseEnter& onMouseEnterEvent) {
                        (void) container; // skip it

                        for(auto& component : _components) {
                            glm::vec2 newPosition = onMouseEnterEvent.position - component->getPosition() + getOffset();

                            if(newPosition.x >= 0 && newPosition.x < component->getSize().x &&
                               newPosition.y >= 0 && newPosition.y < component->getSize().y)
                            {
                                _componentsUnderMouse.insert(component.get());
                                component->onMouseEnter(*component, { newPosition });
                            }
                        }
                    }
                );

                // MouseMove
                onMouseMove += Event::MouseMove::Handler(
                    "__GLUL::GUI::Event::MouseMove::Forwarding",
                    [&](Component& container, const Event::MouseMove& onMouseMoveEvent) {
                        (void) container; // skip it

                        for(auto& component : _components) {
                            glm::vec2 newPosition = onMouseMoveEvent.position - component->getPosition() + getOffset();

                            bool wasUnderMouseBefore = isUnderMouse(*component); // returns result from previous frame
                            bool isUnderMouseNow = (newPosition.x >= 0 && newPosition.x < component->getSize().x &&
                                                    newPosition.y >= 0 && newPosition.y < component->getSize().y);

                            if(isUnderMouseNow) {
                                if(wasUnderMouseBefore) {
                                    component->onMouseMove(*component, { newPosition });
                                } else {
                                    _componentsUnderMouse.insert(component.get());
                                    component->onMouseEnter(*component, { newPosition });
                                }
                            } else {
                                if(wasUnderMouseBefore) {
                                    _componentsUnderMouse.erase(component.get());
                                    component->onMouseLeave(*component, { });
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

                        for(auto& component : _components)
                            if(component->isEnabled() && component->isFocused())
                                component->onTextInput(*component, onTextInputEvent);
                    }
                );
            }

            void Container::_rebuildBatch() const {
                _batch.clear();

                for(auto& component : _components)
                    if(component->isVisible())
                        component->_pushToBatch(_batch);

                _batch.compute();
                _batch.clearLocal();
            }

            void Container::_setupClipping() const {
                _wasScissorTestActive = GL::Context::Current->isScissorTestEnabled();

                if(_wasScissorTestActive)
                    _scissorTestBox = GL::Context::Current->getScissorBox();

                auto windowSize = GL::Context::Current->getViewportSize();
                auto containerBounds = getBounds();

                containerBounds.setPosition({
                    containerBounds.getPosition().x,
                    windowSize.y - containerBounds.getPosition().y - getSize().y
                });

                GL::Context::Current->setScissorBox(containerBounds);
            }

            void Container::_revertClipping() const {
                if(_wasScissorTestActive)
                    GL::Context::Current->setScissorBox(_scissorTestBox);
                else
                    GL::Context::Current->disableScissorTest();
            }

            void Container::_pushToBatch(G2D::TexturedBatch& texBatch) const {
                (void) texBatch; // unused

                // don't push anything to parent container
            }

        }

    }

}
