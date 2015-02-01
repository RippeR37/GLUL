#ifndef UTILS_GL_GUI_CONTAINER_H_INCLUDED
#define UTILS_GL_GUI_CONTAINER_H_INCLUDED

#include <Utils/GL+/GUI/Component.h>

#include <list>

namespace GL {

    namespace GUI {

        class Container : public Component {
            public:
                Container();
                virtual ~Container();

                virtual void render();
                virtual void update(double deltaTime);

                void add(Component* const component);
                void validate();

                void setInvalid();

                bool isValid() const;

            private:
                void setValid();
                void handleChildDestruction(Component* component);

                bool _isValid;
                std::list<Component*> _components;

            public:
                friend Component;
        };

    }

}

#endif