#ifndef UTILS_GL_GUI_COMPONENT_H_INCLUDED
#define UTILS_GL_GUI_COMPONENT_H_INCLUDED

#include "Event.h"
#include "../../Rectangle.h"

#include <glm/vec2.hpp>

#include <functional>
#include <vector>

namespace GL {

    namespace GUI {

        class Container;

        class Component {
            public:
                Component();
                Component(Container* const parent);
                virtual ~Component();
                
                virtual void render() = 0;
                virtual void update(double deltaTime) = 0;
                
                void processEvent(const Event& event);
                
                void addListener(Event::Type eventType, std::function<void(const Event&)> function);
                void clearListeners();
                void clearListeners(Event::Type eventType);

                bool isEnabled() const;
                bool isFocused() const;
                bool isVisible() const;

                const glm::vec2& getSize() const;
                const Util::Point& getPosition() const;
                Container* const getParent() const;
                
                const Util::Point getScreenPosition() const;
                const Util::Rectangle getBounds() const;

                void setEnabled(bool flag);
                void setFocused(bool flag);
                void setVisible(bool flag);
                
                virtual void setSize(const glm::vec2& size);
                void setPosition(const Util::Point& position);

            protected:
                void setParent(Container* const parent);
                void notifyDestructionParent();
                void notifyInvalidParent();

                bool _isEnabled;
                bool _isFocused;
                bool _isVisible;

                glm::vec2 _size;
                Util::Point _position;
                Container* _parent;

                std::vector<std::vector<std::function<void(const Event&)>>> _listeners;

            public:
                friend Container;
        };

    }

}

#endif 