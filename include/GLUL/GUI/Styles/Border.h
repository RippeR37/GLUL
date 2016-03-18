#pragma once

#include <GLUL/GUI/Component.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace GLUL {

    namespace GUI {

        namespace Style {

            class GLUL_API Border {
                public:
                    Border(Component& component);

                    Border& operator=(const Border&) = delete;

                    void set(unsigned int width);
                    void set(unsigned int width, int offset);
                    void set(unsigned int width, int offset, const glm::vec3& color);
                    void set(unsigned int width, int offset, const glm::vec4& color);

                    Border& setWidth(unsigned int width);
                    Border& setOffset(int offset);
                    Border& setColor(const glm::vec3& color);
                    Border& setColor(const glm::vec4& color);

                    unsigned int getWidth() const;
                    int getOffset() const;
                    const glm::vec4& getColor() const;

                private:
                    void _setWidth(unsigned int width);
                    void _setOffset(int offset);
                    void _setColor(const glm::vec3& color);
                    void _setColor(const glm::vec4& color);

                    void updateComponent();

                    unsigned int _width;
                    int _offset;
                    glm::vec4 _color;
                    Component& _component;
            };

        }

    }

}
