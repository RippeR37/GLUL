#pragma once

#include <GLUL/Rectangle.h>
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

                virtual const Container& render() const;
                virtual Container& update(double deltaTime);
                virtual const Container& validate() const;

                virtual Container& add(Component& component);
                virtual Container& add(Component* const component);

                virtual const glm::vec2 getOffset() const;

                virtual Container& setInvalid();
                virtual Container& setFocused(bool flag);

            private:
                void notifyChildsOfInvalidState();
                void handleChildDestruction(Component* component);
                void initializeEventForwarding();

                bool isUnderMouse(Component* component) const;

                void setupClipping() const;
                void enableClipping() const;
                void revertClipping() const;


                bool _wasScissorTestActive;
                GLUL::Rectangle _scissorTestBox;
                std::list<Component*> _components;
                std::set<Component*> _componentsUnderMouse;

            public:
                friend Component;
        };

    }

}
