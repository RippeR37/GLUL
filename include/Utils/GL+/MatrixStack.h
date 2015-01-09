#ifndef UTILS_GL_MATRIXSTACK_H_INCLUDED
#define UTILS_GL_MATRIXSTACK_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>

#include <stack>

namespace GL {

    class MatrixStack {
        public:
            MatrixStack();
            ~MatrixStack();

            void loadID();
            void loadMatrix(const glm::mat4& matrix);
            void multiplyMatrix(const glm::mat4& matrix);

            void popMatrix();
            void pushMatrix();
            void pushMatrix(const glm::mat4& matrix);

            void rotate(float angle, float x, float y, float z);
            void rotate(float angle, const glm::vec3& vector);

            void translate(float x, float y, float z);
            void translate(const glm::vec3& vector);

            void scale(float x, float y, float z);
            void scale(const glm::vec3& vector);

            const glm::mat4& getMatrix() const;

        private:
            std::stack<glm::mat4> _stack;
            
    };

}

#endif