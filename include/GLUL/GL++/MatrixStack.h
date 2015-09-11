#pragma once

#include <GLUL/Config.h>

#include <GL/glew.h>
#include <glm/matrix.hpp>

#include <stack>


namespace GL {

    class GLUL_API MatrixStack {
        public:
            MatrixStack();
            ~MatrixStack();

            MatrixStack& operator*=(const glm::mat4& matrix);   // alias for multiply(const glm::mat4&)
            MatrixStack& operator+=(const glm::mat4& matrix);   // alias for push(const glm::mat4&)
            MatrixStack& operator<<(const glm::mat4& matrix);   // alias for push(const glm::mat4&)
            MatrixStack& operator>>(glm::mat4& matrix);         // alias for pop() with value assignment
            MatrixStack& operator--();                          // alias for pop()
            MatrixStack& operator++();                          // alias for push()

            void clear();

            void set();
            void set(const glm::mat4& matrix);
            void multiply(const glm::mat4& matrix);

            void pop();
            void push();
            void push(const glm::mat4& matrix);
            void load(const glm::mat4& matrix);

            void rotate(float angle, float x, float y, float z);
            void rotate(float angle, const glm::vec3& vector);

            void translate(float x, float y, float z);
            void translate(const glm::vec3& vector);

            void scale(float x, float y, float z);
            void scale(const glm::vec3& vector);

            const glm::mat4& get() const;

        private:
            std::stack<glm::mat4> _stack;
            
    };

}
