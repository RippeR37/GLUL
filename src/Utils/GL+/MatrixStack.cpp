#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include <Utils/GL+/MatrixStack.h>

#include <glm/gtc/matrix_transform.hpp>

namespace GL {

    MatrixStack::MatrixStack() {
        _stack.push(glm::mat4(1.0f));
    }

    MatrixStack::~MatrixStack() {

    }


    void MatrixStack::loadID() {
        loadMatrix(glm::mat4(1.0f));
    }

    void MatrixStack::loadMatrix(const glm::mat4& matrix) {
        _stack.top() = matrix;
    }

    void MatrixStack::multiplyMatrix(const glm::mat4& matrix) {
        _stack.top() *= matrix;
    }


    void MatrixStack::popMatrix() {
        _stack.pop();
    }

    void MatrixStack::pushMatrix() {
        pushMatrix(_stack.top());
    }

    void MatrixStack::pushMatrix(const glm::mat4& matrix) {
        _stack.push(matrix);
    }


    void MatrixStack::rotate(float angle, float x, float y, float z) {
        rotate(angle, glm::vec3(x, y, z));
    }

    void MatrixStack::rotate(float angle, const glm::vec3& vector) {
        _stack.top() = glm::rotate(_stack.top(), angle, vector);
    }


    void MatrixStack::translate(float x, float y, float z) {
        translate(glm::vec3(x, y, z));
    }

    void MatrixStack::translate(const glm::vec3& vector) {
        _stack.top() = glm::translate(_stack.top(), vector);
    }


    void MatrixStack::scale(float x, float y, float z) {
        scale(glm::vec3(x, y, z));
    }

    void MatrixStack::scale(const glm::vec3& vector) {
        _stack.top() = glm::scale(_stack.top(), vector);
    }


    const glm::mat4& MatrixStack::getMatrix() const {
        return _stack.top();
    }

}