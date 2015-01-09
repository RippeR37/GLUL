#include <Utils/GL+/VertexArray.h>
#include <Utils/Exception.h>

#include <utility>

namespace GL {

    VertexArray::VertexArray() {
        create();
    }
    
    VertexArray::VertexArray(VertexArray&& vao) {
        create();

        std::swap(_vaoID, vao._vaoID);
        std::swap(_isDrawTargetSet, vao._isDrawTargetSet);
        std::swap(_isDrawCountSet,  vao._isDrawCountSet);
        std::swap(_drawOffset, vao._drawOffset);
        std::swap(_drawTarget, vao._drawTarget);
        std::swap(_drawCount,  vao._drawCount);
        std::swap(_attachedVBOs, vao._attachedVBOs);
    }

    VertexArray::~VertexArray() {
        destroy();
    }

    VertexArray& VertexArray::operator=(VertexArray&& vao) {
        std::swap(_vaoID, vao._vaoID);
        std::swap(_isDrawTargetSet, vao._isDrawTargetSet);
        std::swap(_isDrawCountSet,  vao._isDrawCountSet);
        std::swap(_drawOffset, vao._drawOffset);
        std::swap(_drawTarget, vao._drawTarget);
        std::swap(_drawCount,  vao._drawCount);
        std::swap(_attachedVBOs, vao._attachedVBOs);

        return *this;
    }

    void VertexArray::bind() const {
        glBindVertexArray(_vaoID);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }

    void VertexArray::drawArrays() const {
        if(_isDrawTargetSet && _isDrawCountSet)
            glDrawArrays(static_cast<GLenum>(getDrawTarget()), getDrawOffset(), getDrawCount());
        else
            throw Util::Exception::FatalError(std::string("Attempt to drawArrays() without setting target/offset/count before"));
    }

    void VertexArray::enableAttrib(GLuint index) {
        glEnableVertexAttribArray(index);
    }

    void VertexArray::disableAttrib(GLuint index) {
        glDisableVertexAttribArray(index);
    }

    void VertexArray::attachVBO(const VertexBuffer* vertexBuffer) {
        _attachedVBOs.push_back(vertexBuffer);
    }

    void VertexArray::setAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    }
    
    void VertexArray::setAttribPointers() {
        for(const VertexBuffer* vbo : _attachedVBOs) {
            if(vbo != nullptr)
                setAttribPointers(*vbo);
        }
    }

    void VertexArray::setAttribPointers(const VertexBuffer& vertexBuffer) {
        vertexBuffer.bind();
            setAttribPointers(vertexBuffer.getAttributes());
        vertexBuffer.unbind();
    }

    void VertexArray::setAttribPointers(const std::list<VertexAttrib>& attributes) {
        for(const VertexAttrib& attrib : attributes) {
            enableAttrib(attrib.index);
            setAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, attrib.stride, attrib.offset);
        }
    }

    void VertexArray::setDrawOffset(GLint offset) {
        _drawOffset = offset;
    }

    void VertexArray::setDrawCount(GLsizei count) {
        _drawCount = count;
        _isDrawCountSet = true;
    }

    void VertexArray::setDrawTarget(DrawTarget target) {
        _drawTarget = target;
        _isDrawTargetSet = true;
    }

    GLint VertexArray::getDrawOffset() const {
        return _drawOffset;
    }

    GLsizei VertexArray::getDrawCount() const {
        return _drawCount;
    }

    VertexArray::DrawTarget VertexArray::getDrawTarget() const {
        return _drawTarget;
    }

    GLuint VertexArray::getID() const {
        return _vaoID;
    }
    
    const std::list<const VertexBuffer*>& VertexArray::getAttachedVBOs() const {
        return _attachedVBOs;
    }

    void VertexArray::create() {
        glGenVertexArrays(1, &_vaoID);

        _isDrawTargetSet = false;
        _isDrawCountSet  = false;
        
        setDrawOffset(0);
    }

    void VertexArray::destroy() {
        glDeleteVertexArrays(1, &_vaoID);
    }

}