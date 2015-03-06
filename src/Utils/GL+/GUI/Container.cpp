#include <Utils/GL+/GUI/Container.h>

namespace GL {

    namespace GUI {

        Container::Container(Container* const parent) : Component(parent) {

        }

        Container::~Container() {
            for(auto& component : _components) {
                component->setParent(nullptr);
                delete component;
                component = nullptr;
            }
            _components.clear();

            setInvalid();
        }
        
        void Container::add(Component* const component) {
            _components.push_back(component);

            setInvalid();
        }

        void Container::render() {
            for(auto component : _components)
                if(component)
                    component->render();
        }

        void Container::update(double deltaTime) {
            for(auto component : _components)
                if(component)
                    component->update(deltaTime);
        }

        void Container::validate() {
            if(isValid())
                return;

            // validate

            setValid();
        }

        void Container::setInvalid() {
            _isValid = false;
        }
        
        bool Container::isValid() const {
            return _isValid;
        }

        void Container::setValid() {
            _isValid = true;
        }

        void Container::handleChildDestruction(Component* component) {
            _components.remove(component);

            setInvalid();
        }

    }

}