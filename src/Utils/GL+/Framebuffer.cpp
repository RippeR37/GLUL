#include <Utils/GL+/Framebuffer.h>

namespace GL {

    Framebuffer::Framebuffer() {
        create();
    }

    Framebuffer::Framebuffer(Framebuffer&& framebuffer) {
        _framebufferID = 0;

        std::swap(_framebufferID, framebuffer._framebufferID);
    }

    Framebuffer::~Framebuffer() {
        destroy();
    }

    void Framebuffer::bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, getID());
    }

    void Framebuffer::unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    GLuint Framebuffer::getID() const {
        return _framebufferID;
    }

    void Framebuffer::create() {
        glGenFramebuffers(1, &_framebufferID);
    }

    void Framebuffer::destroy() {
        glDeleteFramebuffers(1, &_framebufferID);
    }

}