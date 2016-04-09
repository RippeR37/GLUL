#pragma once

#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>
#include <GLUL/GUI/Container.h>
#include <GLUL/GUI/Slider.h>
#include <GLUL/GUI/Styles/Border.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <vector>


namespace GLUL {

    namespace GUI {

        class GLUL_API Panel : public Container {
            public:
                Panel(Container& parent, const glm::vec2& position, const glm::vec2& size);
                Panel(Container& parent, const glm::vec2& position, const glm::vec2& size, const glm::vec2& totalSize);
                Panel(Container* const parent, const glm::vec2& position, const glm::vec2& size);
                Panel(Container* const parent, const glm::vec2& position, const glm::vec2& size, const glm::vec2& totalSize);
                
                ~Panel();

                void bindTo(Container& container);
                void bindTo(Container* container);

                const Panel& render() const;
                Panel& update(double deltaTime);
                const Panel& validate() const;

                const glm::vec2 getScreenPosition() const;
                const glm::vec2 getOffset() const;
                const glm::vec2& getTotalSize() const;
                const glm::vec4& getBackgroundColor() const;
                float getBackgroundAlpha() const;
                bool isHorizontalScrollbarVisible() const;
                bool isVerticalScrollbarVisible() const;

                Panel& setSize(const glm::vec2& size);
                Panel& setTotalSize(const glm::vec2& totalSize);
                Panel& setPosition(const glm::vec2& position);
                Panel& setBackgroundColor(const glm::vec3& backgroundColor);
                Panel& setBackgroundColor(const glm::vec4& backgroundColor);


            public:
                Slider scrollbarHorizontal;
                Slider scrollbarVertical;


            protected:
                void _initializeScrollbars();
                void _updateScrollbarLogic();

                static GL::Program& getProgram();
                std::vector<glm::vec4> getVertices() const;


            protected:
                bool _glInitialized;
                glm::vec2 _totalSize;
                glm::vec4 _backgroundColor;
                GL::VertexArray _vao;
                GL::VertexBuffer _vbo;

        };

    }

}
