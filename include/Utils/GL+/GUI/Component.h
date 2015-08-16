#ifndef UTILS_GL_GUI_COMPONENT_H_INCLUDED
#define UTILS_GL_GUI_COMPONENT_H_INCLUDED

#include <Utils/Rectangle.h>
#include <Utils/GL+/GUI/Events/HandlerAggregator.h>
#include <Utils/GL+/GUI/Events/OnClick.h>

#include <glm/vec2.hpp>

#include <functional>
#include <vector>

namespace GL {

    namespace GUI {

        class Container;

        class Component {
            public:
                Component(Container& parent);
                Component(Container* const parent = nullptr);
                virtual ~Component();
                
                void bindTo(Container& container);
                void bindTo(Container* container);

                virtual void render() const = 0;
                virtual void update(double deltaTime) = 0;

                virtual void validate() const;

                bool isEnabled() const;
                bool isFocused() const;
                bool isVisible() const;
                bool isValid() const;

                const glm::vec2& getSize() const;
                const Util::Point& getPosition() const;
                const Container* getParent() const;
                Container* getParent();
                
                const Util::Point getScreenPosition() const;
                const Util::Rectangle getBounds() const;

                virtual void setEnabled(bool flag);
                virtual void setFocused(bool flag);
                virtual void setVisible(bool flag);
                virtual void setInvalid();
                
                virtual void setSize(const glm::vec2& size);
                virtual void setPosition(const glm::vec2& position);
                virtual void setPosition(const Util::Point& position);

            public:
                Event::HandlerAggregator<Event::OnClick> onClick;

            protected:
                void setValid();
                void setParent(Container* const parent);
                void notifyParentOfDestruction();

                bool _isEnabled;
                bool _isFocused;
                bool _isVisible;
                bool _isValid;

                glm::vec2 _size;
                Util::Point _position;
                Container* _parent;

            public:
                friend Container;
        };

    }

}

#endif 