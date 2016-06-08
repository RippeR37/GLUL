#pragma once

#include <GLUL/Config.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API Component;

            class GLUL_API Mark {
            public:
                Mark(const Component& owner);
                Mark(const Component& owner, float scale, const glm::vec3& color);
                Mark(const Component& owner, float scale, const glm::vec4& color);
                Mark(const Component& owner, const glm::vec2& scale, const glm::vec3& color);
                Mark(const Component& owner, const glm::vec2& scale, const glm::vec4& color);
                virtual ~Mark() = default;

                Mark(const Mark&) = delete;
                Mark& operator=(const Mark&) = delete;

                const glm::vec4& getColor() const;
                const glm::vec2& getScale() const;

                void set(float scale, const glm::vec3& color);
                void set(float scale, const glm::vec4& color);
                void set(const glm::vec2& scale, const glm::vec3& color);
                void set(const glm::vec2& scale, const glm::vec4& color);
                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);
                void setScale(float scale);
                void setScale(const glm::vec2& scale);

            protected:
                void _invalidate();

                const Component& _owner;
                glm::vec2 _scale;
                glm::vec4 _color;

                friend class ComponentWithBackground;
            };

        }

    }

}
