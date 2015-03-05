#include <Utils/GL+/Framebuffer.h>

namespace GL {

    Framebuffer::Framebuffer() {
        _isCreated = false;
    }

    Framebuffer::Framebuffer(Framebuffer&& framebuffer) {
        _isCreated = false;

        std::swap(_isCreated,     framebuffer._isCreated);
        std::swap(_framebufferID, framebuffer._framebufferID);
    }

    Framebuffer::~Framebuffer() {
        destroy();
    }

    Framebuffer& Framebuffer::operator=(Framebuffer&& framebuffer) {
        _isCreated = false;

        std::swap(_isCreated, framebuffer._isCreated);
        std::swap(_framebufferID, framebuffer._framebufferID);

        return *this;
    }

    void Framebuffer::create() {
        destroy();

        glGenFramebuffers(1, &_framebufferID);
        _isCreated = true;
    }

    void Framebuffer::destroy() {
        if(isCreated()) {
            glDeleteFramebuffers(1, &_framebufferID);

            _isCreated = false;
        }
    }

    void Framebuffer::bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, getID());
    }

    void Framebuffer::unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    GLuint Framebuffer::getID() const {
        if(!isCreated())
            const_cast<Framebuffer*>(this)->create();

        return _framebufferID;
    }

}