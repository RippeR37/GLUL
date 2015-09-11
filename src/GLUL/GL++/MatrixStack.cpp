#include <GLUL/GL++/MatrixStack.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

namespace GL {

    MatrixStack::MatrixStack() {
        _stack.push(glm::mat4(1.0f));
    }

    MatrixStack::~MatrixStack() {

    }

    MatrixStack& MatrixStack::operator*=(const glm::mat4& matrix) {
        multiply(matrix);
        return *this;
    }

    MatrixStack& MatrixStack::operator+=(const glm::mat4& matrix) {
        push(matrix);
        return *this;
    }

    MatrixStack& MatrixStack::operator<<(const glm::mat4& matrix) {
        load(matrix);
        return *this;
    }

    MatrixStack& MatrixStack::operator>>(glm::mat4& matrix) {
        matrix = get();
        pop();
        return *this;
    }

    MatrixStack& MatrixStack::operator--() {
        pop();
        return *this;
    }

    MatrixStack& MatrixStack::operator++() {
        push();
        return *this;
    }

    void MatrixStack::clear() {
        while(_stack.empty() == false)
            _stack.pop();

        _stack.push(glm::mat4(1.0));
    }

    void MatrixStack::set() {
        set(glm::mat4(1.0f));
    }

    void MatrixStack::set(const glm::mat4& matrix) {
        _stack.top() = matrix;
    }

    void MatrixStack::multiply(const glm::mat4& matrix) {
        _stack.top() *= matrix;
    }

    void MatrixStack::pop() {
        _stack.pop();
    }

    void MatrixStack::push() {
        push(_stack.top());
    }

    void MatrixStack::push(const glm::mat4& matrix) {
        _stack.push(matrix);
    }

    void MatrixStack::load(const glm::mat4& matrix) {
        _stack.top() = matrix;
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


    const glm::mat4& MatrixStack::get() const {
        return _stack.top();
    }

}
