#include <Utils/GL+/Uniform.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GL {

    Uniform::Uniform() {
        _location = -1;
    }

    Uniform::Uniform(GLuint location) {
        _location = location;
    }

    Uniform::~Uniform() {

    }

    GLuint Uniform::getLocation() const {
        return _location;
    }

    void Uniform::setSampler(GLint value) {
        glUniform1i(_location, value);
    }

    //glUniform1_()
    template<> void Uniform::set(GLfloat v0) {
        glUniform1f(_location, v0);
    }
    template<> void Uniform::set(GLint v0) {
        glUniform1i(_location, v0);
    }
    template<> void Uniform::set(GLuint v0) {
        glUniform1ui(_location, v0);
    }

    //glUniform2_()
    template<> void Uniform::set(GLfloat v0, GLfloat v1) {
        glUniform2f(_location, v0, v1);
    }
    template<> void Uniform::set(GLint v0, GLint v1) {
        glUniform2i(_location, v0, v1);
    }
    template<> void Uniform::set(GLuint v0, GLuint v1) {
        glUniform2ui(_location, v0, v1);
    }

    //glUniform3_()
    template<> void Uniform::set(GLfloat v0, GLfloat v1, GLfloat v2) {
        glUniform3f(_location, v0, v1, v2);
    }
    template<> void Uniform::set(GLint v0, GLint v1, GLint v2) {
        glUniform3i(_location, v0, v1, v2);
    }
    template<> void Uniform::set(GLuint v0, GLuint v1, GLuint v2) {
        glUniform3ui(_location, v0, v1, v2);
    }

    //glUniform4_
    template<> void Uniform::set(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
        glUniform4f(_location, v0, v1, v2, v3);
    }
    template<> void Uniform::set(GLint v0, GLint v1, GLint v2, GLint v3) {
        glUniform4i(_location, v0, v1, v2, v3);
    }
    template<> void Uniform::set(GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
        glUniform4ui(_location, v0, v1, v2, v3);
    }

    //glUniform2_v
    template<> void Uniform::setVec(const glm::vec2& value, GLsizei count) {
        glUniform2fv(_location, count, glm::value_ptr(value));
    }
    template<> void Uniform::setVec(const glm::ivec2& value, GLsizei count) {
        glUniform2iv(_location, count, glm::value_ptr(value));
    }
    template<> void Uniform::setVec(const glm::uvec2& value, GLsizei count) {
        glUniform2uiv(_location, count, glm::value_ptr(value));
    }

    //glUniform3_v
    template<> void Uniform::setVec(const glm::vec3& value, GLsizei count) {
        glUniform3fv(_location, count, glm::value_ptr(value));
    }
    template<> void Uniform::setVec(const glm::ivec3& value, GLsizei count) {
        glUniform3iv(_location, count, glm::value_ptr(value));
    }
    template<> void Uniform::setVec(const glm::uvec3& value, GLsizei count) {
        glUniform3uiv(_location, count, glm::value_ptr(value));
    }

    //glUniform4_v
    template<> void Uniform::setVec(const glm::vec4& value, GLsizei count) {
        glUniform4fv(_location, count, glm::value_ptr(value));
    }
    template<> void Uniform::setVec(const glm::ivec4& value, GLsizei count) {
        glUniform4iv(_location, count, glm::value_ptr(value));
    }
    template<> void Uniform::setVec(const glm::uvec4& value, GLsizei count) {
        glUniform4uiv(_location, count, glm::value_ptr(value));
    }

    //glUniformMatrix_fv
    template<> void Uniform::setMatrix(const glm::mat2& value, GLsizei count, GLboolean transpose) {
        glUniformMatrix2fv(_location, count, transpose, glm::value_ptr(value));
    }
    template<> void Uniform::setMatrix(const glm::mat3& value, GLsizei count, GLboolean transpose) {
        glUniformMatrix3fv(_location, count, transpose, glm::value_ptr(value));
    }
    template<> void Uniform::setMatrix(const glm::mat4& value, GLsizei count, GLboolean transpose) {
        glUniformMatrix4fv(_location, count, transpose, glm::value_ptr(value));
    }

    //glUniformMatrix_x_fv
    template<> void Uniform::setMatrix(const glm::mat2x3& value, GLsizei count, GLboolean transpose) {
        glUniformMatrix2x3fv(_location, count, transpose, glm::value_ptr(value));
    }
    template<> void Uniform::setMatrix(const glm::mat2x4& value, GLsizei count, GLboolean transpose) {
        glUniformMatrix2x4fv(_location, count, transpose, glm::value_ptr(value));
    }
    template<> void Uniform::setMatrix(const glm::mat3x4& value, GLsizei count, GLboolean transpose) {
        glUniformMatrix3x4fv(_location, count, transpose, glm::value_ptr(value));
    }
    template<> void Uniform::setMatrix(const glm::mat4x2& value, GLsizei count, GLboolean transpose) {
        glUniformMatrix4x2fv(_location, count, transpose, glm::value_ptr(value));
    }
    template<> void Uniform::setMatrix(const glm::mat4x3& value, GLsizei count, GLboolean transpose) {
        glUniformMatrix4x3fv(_location, count, transpose, glm::value_ptr(value));
    }

}