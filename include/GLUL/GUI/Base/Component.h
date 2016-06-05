#pragma once

#include <GLUL/G2D/Rectangle.h>
#include <GLUL/G2D/TexturedBatch.h>
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


namespace GLUL {

    namespace GUI {

        class Container;

        class GLUL_API Component {
            public:
                virtual ~Component() = default;

                virtual void render() const;
                virtual void update(double deltaTime);
                virtual void validate() const;

                bool isEnabled() const;
                bool isFocused() const;
                bool isVisible() const;
                bool isValid() const;
                bool isUnderMouse() const;

                const Container& getParent() const;

                virtual const glm::vec2& getSize() const;
                virtual const glm::vec2& getPosition() const;
                virtual const glm::vec2 getScreenPosition() const;
                virtual const G2D::Rectangle getBounds() const;

                virtual void setInvalid() const;
                virtual void setEnabled(bool flag);
                virtual void setFocused(bool flag);
                virtual void setVisible(bool flag);
                virtual void setSize(const glm::vec2& size);
                virtual void setPosition(const glm::vec2& position);

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
                Component(const Container& parent);
                Component(const Container& parent, const glm::vec2& size, const glm::vec2& position);

                Component(const Component&) = delete;
                Component& operator=(const Component&) = delete;

                void _setValid() const;
                virtual void _pushToBatch(G2D::TexturedBatch& texBatch) const = 0;

                const Container& _parent;
                glm::vec2 _size;
                glm::vec2 _position;
                bool _isEnabled;
                bool _isFocused;
                bool _isVisible;
                mutable bool _isValid;

                friend class Container;
        };

    }

}
