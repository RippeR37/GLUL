#pragma once

#include <GLUL/Config.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API Component;

            class GLUL_API Border {
                public:
                    Border(const Component& owner);
                    Border(const Component& owner, unsigned int width, const glm::vec3& color);
                    Border(const Component& owner, unsigned int width, const glm::vec4& color);
                    virtual ~Border() = default;

                    Border(const Border&) = delete;
                    Border& operator=(const Border&) = delete;

                    unsigned int getWidth() const;
                    const glm::vec4& getColor() const;

                    void setWidth(unsigned int width);
                    void setColor(const glm::vec3& color);
                    void setColor(const glm::vec4& color);

                protected:
                    void _invalidate();

                    const Component& _owner;
                    unsigned int _width;
                    glm::vec4 _color;

                    friend class ComponentWithBackground;
            };

        }

    }

}
