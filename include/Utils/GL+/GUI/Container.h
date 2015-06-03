#ifndef UTILS_GL_GUI_CONTAINER_H_INCLUDED
#define UTILS_GL_GUI_CONTAINER_H_INCLUDED

#include <Utils/GL+/GUI/Component.h>

#include <list>

namespace GL {

    namespace GUI {

        class Container : public Component {
            public:
                Container(Container* const parent = nullptr);
                virtual ~Container();

                virtual void render() const;
                virtual void update(double deltaTime);
                virtual void validate() const;

                virtual void add(Component* const component);

                virtual void setInvalid();

            private:
                void notifyChildsOfInvalidState();
                void handleChildDestruction(Component* component);

                std::list<Component*> _components;

            public:
                friend Component;
        };

    }

}

#endif