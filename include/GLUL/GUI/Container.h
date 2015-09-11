#pragma once

#include <GLUL/GUI/Component.h>

#include <list>
#include <set>


namespace GLUL {

    namespace GUI {

        class GLUL_API Container : public Component {
            public:
                Container(Container& parent);
                Container(Container* const parent = nullptr);
                virtual ~Container();

                virtual void render() const;
                virtual void update(double deltaTime);
                virtual void validate() const;

                virtual void add(Component& component);
                virtual void add(Component* const component);

                virtual void setInvalid();
                virtual void setFocused(bool flag);

            private:
                void notifyChildsOfInvalidState();
                void handleChildDestruction(Component* component);
                void initializeEventForwarding();

                bool isUnderMouse(Component* component) const;

                std::list<Component*> _components;
                std::set<Component*> _componentsUnderMouse;

            public:
                friend Component;
        };

    }

}
