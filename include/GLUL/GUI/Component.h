#pragma once

#include <GLUL/G2D/Rectangle.h>
#include <GLUL/GUI/Events/Focus.h>
#include <GLUL/GUI/Events/FocusLoss.h>
#include <GLUL/GUI/Events/HandlerAggregator.hpp>
#include <GLUL/GUI/Events/KeyStroke.h>
#include <GLUL/GUI/Events/MouseClick.h>
#include <GLUL/GUI/Events/MouseRelease.h>
#include <GLUL/GUI/Events/MouseEnter.h>
#include <GLUL/GUI/Events/MouseLeave.h>
#include <GLUL/GUI/Events/MouseMove.h>
#include <GLUL/GUI/Events/TextInput.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <functional>
#include <vector>


namespace GLUL {

    namespace GUI {

        class Container;

        class GLUL_API Component {
            public:
                Component(Container& parent);
                Component(Container* const parent = nullptr);
                virtual ~Component();

                virtual void bindTo(Container& container);
                virtual void bindTo(Container* container);

                virtual const Component& render() const = 0;
                virtual Component& update(double deltaTime) = 0;

                virtual const Component& validate() const;

                bool isEnabled() const;
                bool isFocused() const;
                bool isVisible() const;
                bool isValid() const;

                virtual const glm::vec2& getSize() const;
                virtual const glm::vec2& getPosition() const;
                const Container* getParent() const;
                Container* getParent();

                virtual const glm::vec2 getScreenPosition() const;
                virtual const G2D::Rectangle getBounds() const;

                virtual Component& setEnabled(bool flag);
                virtual Component& setFocused(bool flag);
                virtual Component& setVisible(bool flag);
                virtual Component& setInvalid();

                virtual Component& setSize(const glm::vec2& size);
                virtual Component& setPosition(const glm::vec2& position);

            public:
                Event::HandlerAggregator<Event::Focus> onFocus;
                Event::HandlerAggregator<Event::FocusLoss> onFocusLoss;
                Event::HandlerAggregator<Event::KeyStroke> onKeyStroke;
                Event::HandlerAggregator<Event::MouseClick> onMouseClick;
                Event::HandlerAggregator<Event::MouseRelease> onMouseRelease;
                Event::HandlerAggregator<Event::MouseEnter> onMouseEnter;
                Event::HandlerAggregator<Event::MouseLeave> onMouseLeave;
                Event::HandlerAggregator<Event::MouseMove> onMouseMove;
                Event::HandlerAggregator<Event::TextInput> onTextInput;

            protected:
                Component& setValid();
                Component& setParent(Container* const parent);
                void notifyParentOfDestruction();

                bool isUnderMouse() const;

                static void pushColoredRectangle(std::vector<glm::vec4>& result,
                    const glm::vec2& posStart, const glm::vec2& posEnd, const glm::vec4& color);

                static void pushColoredDisk(std::vector<glm::vec4>&result,
                    const glm::vec2& posCenter, float radius, const glm::vec4& color);

                static void pushColoredCircle(std::vector<glm::vec4>&result,
                    const glm::vec2& posCenter, float radius, unsigned int width, const glm::vec4& color);

                bool _isEnabled;
                bool _isFocused;
                bool _isVisible;
                bool _isValid;

                glm::vec2 _size;
                glm::vec2 _position;
                Container* _parent;

            public:
                friend Container;
        };

    }

}
